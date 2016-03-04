#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

#include <qwt_plot.h>

class QwtPlotCurve;

class PlotWidget : public QwtPlot
{
    public:
        enum PlotType
        {
            LINEAR_SPEED    = 0x01,
            ANGULAR_SPEED   = 0x02,
            LINEAR_TARGET   = 0x04,
            ANGULAR_TARGET  = 0x08,
            LINEAR_DUTY     = 0x10,
            ANGULAR_DUTY    = 0x20,
            CUSTOM_PLOT     = 0x40
        };

    private:
        struct PlotCurve
        {
            explicit PlotCurve(QwtPlotCurve* curve, bool nonSig = false) : curve(curve), nonSignificant(nonSig) {}
            void plot();
            void add(double x, double y);

            QwtPlotCurve* curve;
            QList<double> x, y;
            bool nonSignificant;
        };

    public:
        explicit PlotWidget(QWidget *parent = nullptr);

        void addDataToPlot(int idx, float data);

        void clear();

    private:

        QMap<int, PlotWidget::PlotCurve*> m_curves;
};

#endif // PLOTWIDGET_H
