#include "plotwidget.h"

#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_point_data.h>

#include "../timemaster.h"


PlotWidget::PlotWidget(QWidget *parent): QwtPlot(parent)
{
    setCanvasBackground(QColor(Qt::white));

    QwtLegend *legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box);
    insertLegend(legend, QwtPlot::BottomLegend);
    setAxisTitle(QwtPlot::xBottom, "<font color='#000'>t (s)</font>");
    setAxisAutoScale(QwtPlot::xBottom, true);
    setAxisAutoScale(QwtPlot::yLeft, true);
}


void PlotWidget::addDataToPlot(int idx, float data)
{
    QColor color[9] = {Qt::red, Qt::green, Qt::blue, Qt::magenta, Qt::gray, Qt::yellow, Qt::cyan, Qt::darkYellow, Qt::magenta};

    PlotWidget::PlotCurve* current = m_curves.value(idx, nullptr);

    if (!current)
    {
        QString plotTitle;
        switch(idx)
        {
            case LINEAR_SPEED:
                plotTitle = tr("Linear speed");
            break;
            case ANGULAR_SPEED:
                plotTitle = tr("Angular speed");
            break;
            case LINEAR_TARGET:
                plotTitle = tr("Linear target");
            break;
            case ANGULAR_TARGET:
                plotTitle = tr("Angular target");
            break;
            default:
                plotTitle = QString("Plot %1").arg(idx);
        }

        current = new PlotWidget::PlotCurve(new QwtPlotCurve(plotTitle));
        current->curve->attach(this);
        current->curve->setPen(QPen(color[idx % 9]));

        m_curves[idx] = current;
    }

    current->add(TimeMaster::getInstance()->getCurrentTime()/1000.f, data);
    current->plot();

    replot();
    update();
}

void PlotWidget::clear()
{
    for(auto it = m_curves.begin(); it != m_curves.end(); ++it)
    {
        it.value()->curve->detach();
        delete it.value()->curve;
    }
    m_curves.clear();
}


void PlotWidget::PlotCurve::plot()
{
    curve->setData(new QwtPointArrayData(&x[0],&y[0],static_cast<size_t>(x.size())));
}

void PlotWidget::PlotCurve::add(double x, double y)
{
    this->x.push_back(x);
    this->y.push_back(y);
}
