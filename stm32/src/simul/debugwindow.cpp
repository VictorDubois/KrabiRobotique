#include "debugwindow.h"

#include "strategieV2.h"

#include <QDebug>

DebugWindow* DebugWindow::_instance = NULL;

DebugWindow* DebugWindow::getInstance()
{
    if (_instance == NULL)
        _instance = new DebugWindow();
    return _instance;
}

DebugWindow::DebugWindow() :
    QWidget(), parent(NULL), attached(true), ready(false)
#ifdef USE_PLOT
  , plotWidget(0)
#endif
{
    this->setWindowTitle("Krabi Debug");
    setGeometry(0, 0, 240, 600);

    l = new QVBoxLayout();
    l->setAlignment(Qt::AlignTop);
    setLayout(l);

    qlText = new QLabel(this);
    l->addWidget(qlText);

    _instance = this;
}

void DebugWindow::setParent(MainWindow* parent)
{
    this->parent = parent;
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
    qlText->setText(text);
}

void DebugWindow::plot(int index, QString title, float data)
{
#ifdef USE_PLOT
    if (plotWidget == NULL)
    {
        plotWidget = new QwtPlot();
        plotWidget->show();

        l->addWidget(plotWidget);
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

    plotCurves[index]->add(StrategieV2::getTimeSpent() / 1000.f, data);
    plotCurves[index]->plot();

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
