#include "graph.h"

#include <QWidget>
#include <QPainter>

Graph::Graph(QWidget* widget): QWidget(widget)
{
	setAutoFillBackground(true);

    setSamplesLimit(1000);

    setMaxima(2.f, 0.005f);

	QPalette p = palette();
	p.setColor(QPalette::Window,QColor(Qt::darkGray));
	setPalette(p);
}


void Graph::update()
{
    repaint();
}

void Graph::addData(float dataAngular, float dataLinear)
{
    m_vAngular.enqueue(dataAngular);
    m_vLinear.enqueue(dataLinear);

    capData();
}

void Graph::setMaxima(float maxAngular, float maxLinear)
{
    m_maxAngular    = maxAngular;
    m_maxLinear      = maxLinear;
}

void Graph::setSamplesLimit(int max)
{
    max = (max<=10?10:max);

    m_maxSamples = max;
    capData();
}

void Graph::capData()
{
    // This may seems stupid, but it's actually O(2n)
    // (if it's stupid but it works, then it ain't stupid)
    while(m_vAngular.size() > m_maxSamples)
        m_vAngular.dequeue();

    while(m_vLinear.size() > m_maxSamples)
        m_vLinear.dequeue();
}

void Graph::paintEvent(QPaintEvent*)
{
    QPainter p(this);
	p.setRenderHints(QPainter::Antialiasing,true);
	p.setWindow(QRect(0,0,gWidth,gHeight));
	p.setWorldMatrixEnabled(true);


	p.fillRect(0,0,gWidth,gHeight,QColor(255,255,255));
	p.setPen(QColor(Qt::black));

    for (int i=0; i < (m_vLinear.size()-1); ++i)
	{
        p.drawLine(i,-(gHeight/4)*(m_vLinear[i]/m_maxAngular)+gHeight/4,i+1,-(gHeight/4)*(m_vLinear[i+1]/m_maxAngular)+gHeight/4);
    }
    for (int i=0; i < (m_vAngular.size()-1); ++i)
	{
        p.drawLine(i,-(gHeight/4)*(m_vAngular[i]/m_maxLinear)+3*gHeight/4,i+1,-(gHeight/4)*(m_vAngular[i+1]/m_maxLinear)+3*gHeight/4);
    }
}


