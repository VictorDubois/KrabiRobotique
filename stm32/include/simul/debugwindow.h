#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

// to use qwt_plot, please install the 'libqwt-dev' package
// add 'qwt' to CONFIG in .pro to enable this
// sudo apt-get install libqwt-dev (on the VM)
//#define USE_PLOT
#ifdef USE_PLOT
    #include <qwt_plot.h>
    #include <qwt_plot_curve.h>
    #include <qwt_legend.h>
#endif

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

class DebugWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DebugWindow(MainWindow *parent = 0);

    bool isAttached();
    void setReady(bool ready);

    void moveWithoutEvent(QPoint pos);

    void setText(QString text);
    void plot(int index, QString title, float data);

    static DebugWindow* instance();
    
signals:
    
public slots:

private:
    virtual void moveEvent ( QMoveEvent * event );

    static DebugWindow* _instance;

    MainWindow *parent;
    bool attached, ready;

    QLabel* qlText;
    QVBoxLayout* l;

    // plot
#ifdef USE_PLOT
    QwtPlot* plotWidget;
    QMap<int, PlotCurve*> plotCurves;
#endif
    
};

#endif // DEBUGWINDOW_H
