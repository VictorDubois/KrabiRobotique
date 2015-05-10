#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QVBoxLayout>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

#include "bluetoothwindow.h"
#include "bluetoothinterface.h"
#include "odometriewindow.h"
#include "asservwindow.h"

// to use qwt_plot, please install the 'libqwt-dev' package
// add 'qwt' to CONFIG in .pro to enable this
// sudo apt-get install libqwt-dev (on the VM)
#ifdef USE_PLOT
    #include <qwt_plot.h>
    #include <qwt_plot_curve.h>
    #include <qwt_legend.h>
    #include <qwt_point_data.h>
#endif


namespace Ui {
class DebugWindow;
}

class MainWindow;

#ifdef USE_PLOT
struct PlotCurve
{
    PlotCurve(QwtPlotCurve* curve) : curve(curve){}
    void plot();
    void add(double x, double y);

    QwtPlotCurve* curve;
    std::vector<double> x, y;
};
#endif

class DebugWindow : public QMainWindow
{
    Q_OBJECT
public:
    bool isAttached();
    void setReady(bool ready);

    void moveWithoutEvent(QPoint pos);

    void setParent(MainWindow* parent);

    void setText(QString text);
    void plot(int index, QString title, float data);

    BluetoothWindow* getBluetoothWindow();
    BluetoothInterface* getBluetoothInterface();
    OdometrieWindow* getOdometrieWindow();
    AsservWindow* getAsservWindow();

    static DebugWindow* getInstance();
    
signals:
    
public slots:
    void displayBluetoothWindow(bool show);
    void displayBluetoothInterface(bool show);
    void displayOdometrieWindow(bool show);
    void displayAsservWindow(bool show);

    void update();

    void perspectiveAsserv();
    void perspectiveOdometrie();
    void perspectiveSimulateur();

    void hideWindows();

    void clearPlots();

private:
    explicit DebugWindow();
    virtual void moveEvent ( QMoveEvent * event );
    void closeEvent(QCloseEvent *event);

    static DebugWindow* _instance;

    Ui::DebugWindow *ui;

    MainWindow *parent;
    BluetoothWindow* bluetoothWindow;
    BluetoothInterface* bluetoothInterface;
    OdometrieWindow* odometrieWindow;
    AsservWindow* asservWindow;
    bool attached, ready;

    QLabel* statusLabel;
    QPushButton* statusButton;

    // plot
#ifdef USE_PLOT
    QwtPlot* plotWidget;
    QMap<int, PlotCurve*> plotCurves;
#endif
    
};

#endif // DEBUGWINDOW_H
