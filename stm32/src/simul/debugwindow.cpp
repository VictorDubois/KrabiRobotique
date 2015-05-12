#include "debugwindow.h"
#include "ui_debugwindow.h"

#include "strategieV2.h"
#include "table.h"

#include <QDebug>

DebugWindow* DebugWindow::_instance = NULL;

DebugWindow* DebugWindow::getInstance()
{
    if (_instance == NULL)
        _instance = new DebugWindow();
    return _instance;
}

DebugWindow::DebugWindow() :
    QMainWindow(), parent(NULL), attached(true), ready(false), ui(new Ui::DebugWindow), bluetoothWindow(NULL), bluetoothInterface(NULL)
#ifdef USE_PLOT
  , plotWidget(0)
#endif
{
    ui->setupUi(this);

    this->setWindowTitle("Krabi Debug");
    setGeometry(0, 0, 240, 600);

    /*QWidget* widget = new QWidget();
    setCentralWidget(widget);

    l = new QVBoxLayout();
    l->setAlignment(Qt::AlignTop);
    widget->setLayout(l);

    qlText = new QLabel(this);
    l->addWidget(qlText);*/

    connect(ui->actionRemove_objects, SIGNAL(triggered()), Table::getMainInstance(), SLOT(removeAllObjects()));
    connect(ui->actionReset_objects, SIGNAL(triggered()), Table::getMainInstance(), SLOT(createObjects()));
    connect(ui->actionHide_table, SIGNAL(toggled(bool)), Table::getMainInstance(), SLOT(hideTable(bool)));
    connect(ui->actionDisplay_route, SIGNAL(toggled(bool)), Table::getMainInstance(), SLOT(displayRoute(bool)));
    connect(ui->actionDisplay_strategy, SIGNAL(toggled(bool)), Table::getMainInstance(), SLOT(displayStrategy(bool)));
    connect(ui->actionRemote_Mod, SIGNAL(toggled(bool)), Table::getMainInstance(), SLOT(setRemoteMod(bool)));

    connect(ui->actionBluetooth, SIGNAL(toggled(bool)), this, SLOT(displayBluetoothWindow(bool)));
    connect(ui->actionBluetooth_Interface, SIGNAL(toggled(bool)), this, SLOT(displayBluetoothInterface(bool)));
    connect(ui->actionOdometrie, SIGNAL(toggled(bool)), this, SLOT(displayOdometrieWindow(bool)));
    connect(ui->actionAsserv_Window, SIGNAL(toggled(bool)), this, SLOT(displayAsservWindow(bool)));
    connect(ui->actionSharps, SIGNAL(toggled(bool)), this, SLOT(displaySharpWindow(bool)));
    connect(ui->actionWatches, SIGNAL(toggled(bool)), this, SLOT(displayWatchWindow(bool)));

    connect(ui->actionSimulateur, SIGNAL(triggered(bool)), this, SLOT(perspectiveSimulateur()));
    connect(ui->actionAsservissement, SIGNAL(triggered(bool)), this, SLOT(perspectiveAsserv()));
    connect(ui->actionOdom_trie, SIGNAL(triggered(bool)), this, SLOT(perspectiveOdometrie()));

    _instance = this;

    bluetoothWindow = new BluetoothWindow();
    bluetoothInterface = new BluetoothInterface();
    odometrieWindow = new OdometrieWindow();
    asservWindow = new AsservWindow();
    sharpWindow = new SharpWindow();
    watchWindow = new WatchWindow();

    ui->statusbar->insertWidget(0, statusLabel = new QLabel("..."));
    ui->statusbar->insertWidget(1, statusButton = new QPushButton("On"));

    QPushButton* bt = new QPushButton("Clear Plots");
    ui->statusbar->insertWidget(2, bt);
    connect(bt, SIGNAL(clicked(bool)), this, SLOT(clearPlots()));

    statusButton->setFixedWidth(32);
    connect(statusButton, SIGNAL(pressed()), bluetoothWindow, SLOT(bluetoothToggle()));

    update();
}

void DebugWindow::setParent(MainWindow* parent)
{
    this->parent = parent;
}

void DebugWindow::hideWindows()
{
    asservWindow->hide();
    odometrieWindow->hide();
    bluetoothWindow->hide();
    bluetoothInterface->hide();
    sharpWindow->hide();
    watchWindow->hide();
}

void DebugWindow::clearPlots()
{
#ifdef USE_PLOT
    for(QMap<int, PlotCurve*>::iterator it = plotCurves.begin(); it != plotCurves.end(); ++it)
    {
        it.value()->curve->detach();
        delete it.value()->curve;
    }
    plotCurves.clear();
#endif
}

void DebugWindow::perspectiveAsserv()
{
    hideWindows();
    asservWindow->move(mapToGlobal(QPoint(width() + 16, 0)));
    asservWindow->show();

    Table::getMainInstance()->displayRoute(true);
    Table::getMainInstance()->displayStrategy(false);
    Table::getMainInstance()->hideTable(true);

    Table::getMainInstance()->removeAllObjects();

    Table::getMainInstance()->clearRoute();
}

void DebugWindow::perspectiveOdometrie()
{
    hideWindows();
    odometrieWindow->move(mapToGlobal(QPoint(width() + 16, 0)));
    odometrieWindow->show();

    Table::getMainInstance()->displayRoute(true);
    Table::getMainInstance()->displayStrategy(false);
    Table::getMainInstance()->hideTable(true);

    Table::getMainInstance()->removeAllObjects();

    Table::getMainInstance()->clearRoute();
}

void DebugWindow::perspectiveSimulateur()
{
    hideWindows();

    Table::getMainInstance()->displayRoute(false);
    Table::getMainInstance()->displayStrategy(true);
    Table::getMainInstance()->hideTable(false);

    Table::getMainInstance()->createObjects();

    Table::getMainInstance()->clearRoute();
}

void DebugWindow::update()
{
#ifdef BLUETOOTH
    if (bluetoothWindow->isConnecting())
    {
        statusLabel->setText("Bluetooth connecting...");
        statusButton->setText("X");
    }
    else if (bluetoothWindow->isConnected())
    {
        statusLabel->setText("Bluetooth connected");
        statusButton->setText("Off");
    }
    else
    {
        statusLabel->setText("No connection");
        statusButton->setText("On");
    }
#else
    statusLabel->setText("Bluetooth not implemented in Qt4");
    statusButton->hide();
#endif
}

bool DebugWindow::isAttached()
{
    return attached;
}

void DebugWindow::setReady(bool ready)
{
    this->ready = ready;
}

void DebugWindow::moveEvent(QMoveEvent * event)
{
    if (ready)
        attached = false;
}

void DebugWindow::moveWithoutEvent(QPoint pos)
{
    bool currentReady = ready;
    ready = false;

    move(pos);

    ready = currentReady;
}

void DebugWindow::setText(QString text)
{
    ui->infoField->setText(text);
}

void DebugWindow::displayBluetoothWindow(bool show)
{
    toggleWindow(bluetoothWindow, ui->actionBluetooth);
}

void DebugWindow::displayBluetoothInterface(bool show)
{
    toggleWindow(bluetoothInterface, ui->actionBluetooth_Interface);
}

void DebugWindow::displayOdometrieWindow(bool show)
{
    toggleWindow(odometrieWindow, ui->actionOdometrie);
}

void DebugWindow::displayAsservWindow(bool show)
{
    toggleWindow(asservWindow, ui->actionAsserv_Window);
}

void DebugWindow::displaySharpWindow(bool show)
{
    toggleWindow(sharpWindow, ui->actionSharps);
}

void DebugWindow::displayWatchWindow(bool show)
{
    toggleWindow(watchWindow, ui->actionWatches);
}

void DebugWindow::toggleWindow(QWidget* window, QAction* action)
{
    if (window->isHidden())
    {
        if (action != NULL)
            action->setChecked(true);
        window->show();

        window->move(mapToGlobal(QPoint(width() + 16, 0)));
    }
    else
    {
        if (action != NULL)
            action->setChecked(false);
        window->hide();
    }
}

void DebugWindow::closeEvent(QCloseEvent *event)
{
    bluetoothWindow->close();
    bluetoothInterface->close();
    odometrieWindow->close();
    asservWindow->close();
    sharpWindow->close();
    watchWindow->close();
}

BluetoothWindow* DebugWindow::getBluetoothWindow()
{
    return bluetoothWindow;
}

BluetoothInterface* DebugWindow::getBluetoothInterface()
{
    return bluetoothInterface;
}

OdometrieWindow* DebugWindow::getOdometrieWindow()
{
    return odometrieWindow;
}

AsservWindow* DebugWindow::getAsservWindow()
{
    return asservWindow;
}

SharpWindow* DebugWindow::getSharpWindow()
{
    return sharpWindow;
}

WatchWindow* DebugWindow::getWatchWindow()
{
    return watchWindow;
}

void DebugWindow::plot(int index, QString title, float data, int timeTick)
{
#ifdef USE_PLOT
    if (plotWidget == NULL)
    {
        plotWidget = new QwtPlot();
        plotWidget->show();

        ui->centralwidget->layout()->addWidget(plotWidget);
        //plotWidget->setTitle("<font color='#444'>title</font>");
        plotWidget->setCanvasBackground(QColor(Qt::white));

        QwtLegend *legend = new QwtLegend;
        legend->setFrameStyle(QFrame::Box);
        plotWidget->insertLegend(legend, QwtPlot::BottomLegend);

        plotWidget->setAxisTitle(QwtPlot::xBottom, "<font color='#000'>t (s)</font>");
        //plotWidget->setAxisTitle(QwtPlot::yLeft, "<font color='#000'>v</font>");

        plotWidget->setAxisAutoScale(QwtPlot::xBottom, true);
        plotWidget->setAxisAutoScale(QwtPlot::yLeft, true);
    }

    QColor color[9] = {Qt::red, Qt::green, Qt::blue, Qt::magenta, Qt::gray, Qt::yellow, Qt::cyan, Qt::darkYellow, Qt::magenta};

    if (!plotCurves.contains(index))
    {
        plotCurves[index] = new PlotCurve(new QwtPlotCurve(title));
        plotCurves[index]->curve->attach(plotWidget);
        plotCurves[index]->curve->setPen(QPen( color[index % 9] ));
    }

    bool draw = true;
    /*if (data < 0.05f)
    {
        if (plotCurves[index]->nonSignificant)
            draw = false;
        plotCurves[index]->nonSignificant = true;
    }
    else
    {
        if (plotCurves[index]->nonSignificant)
            plotCurves[index]->add(timeTick >= 0 ? (float)timeTick * 0.05f : Table::getMainInstance()->getCurrentTime() - 0.005, 0.f);
        plotCurves[index]->nonSignificant = false;
    }*/

    if (draw)
    {
        plotCurves[index]->add(Table::getMainInstance()->getCurrentTime(), data);
        plotCurves[index]->plot();
    }

    /*ajout = new int[nbrBoisson];
    achat = new double**[nbrBoisson];
    layout = new QGridLayout;
    layout2 = new QGridLayout;

    temps = new double[60];
    for(int i=0;i<60;i++){
    temps[i] = 5.*i/60.;
    }

    for(int i=0;i<nbrBoisson;i++){
        boissonBt[i] = new QPushButton(QString::fromStdString(nomBoisson[i]));
        boissonBt2[i] = new QPushButton(QString::fromStdString(nomBoisson[i]));
        ajout[i]=0;
        achat[i]= new double*[2];
        achat[i][0]=new double[60];
        achat[i][1]=new double[60];
        for(int j=0;j<60;j++){
            achat[i][0][j]= prixBoisson[i];
            achat[i][1][j]= 0;
        }
        QString str;
        str.setNum(prixBoisson[i]);

        boissonBox[i] = new QLabel("<font size='6'  color='#ffffff'>" + str + "</font>");
        boissonBox2[i] = new QLineEdit(str);
        layout->addWidget(boissonBox[i], 0, i);
        layout->addWidget(boissonBt[i], 1, i);
        layout2->addWidget(boissonBox2[i], i, 0);
        layout2->addWidget(boissonBt2[i], i, 1);
        connect(boissonBt2[i],SIGNAL(clicked()),this,SLOT(add()));
        connect(boissonBt[i],SIGNAL(clicked()),this,SLOT(add()));

            QwtPlotCurve *curve = new QwtPlotCurve(boissonBt[i]->text());
            //curve->setData(new Qwt(temps, achat[i][0], 2) );
            curve->attach(simul_plot);
    }*/

    plotWidget->replot();
    plotWidget->update();
#endif
}

#ifdef USE_PLOT
void PlotCurve::plot()
{
    curve->setData(new QwtPointArrayData(&x[0],&y[0],(size_t)x.size()));
}

void PlotCurve::add(double x, double y)
{
    this->x.push_back(x);
    this->y.push_back(y);
}

#endif
