#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

#include <qwt_plot.h>

class QwtPlotCurve;

class PlotWidget : public QwtPlot
{
    private:
        struct PlotCurve
        {
            PlotCurve(QwtPlotCurve* curve, bool nonSig = false) : curve(curve), nonSignificant(nonSig) {}
            void plot();
            void add(double x, double y);

            QwtPlotCurve* curve;
            QList<double> x, y;
            bool nonSignificant;
        };

    public:
        explicit PlotWidget(QWidget *parent = nullptr);

        void addDataToPlot(int idx, float data, QString plotTitle = QString());

    private:

        QMap<int, PlotWidget::PlotCurve*> m_curves;
};

#endif // PLOTWIDGET_H
