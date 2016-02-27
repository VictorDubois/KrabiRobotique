#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <QWidget>
#include <QQueue>


class Graph: public QWidget
{
    public:
        explicit Graph(QWidget* widget);

        void update();

        void setSamplesLimit(int max);

        void addData(float dataAngular, float dataLinear);
        void setMaxima(float maxAngular, float maxLinear);

        static const int gWidth = 1000;
        static const int gHeight = 1000;

    protected:
        void paintEvent(QPaintEvent* evt);

    private:

        void capData();

        QQueue<float> m_vLinear;
        QQueue<float> m_vAngular;

        float m_maxAngular;
        float m_maxLinear;

        int m_maxSamples;
};

#endif

