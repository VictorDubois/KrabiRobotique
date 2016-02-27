#ifndef GRAPHWINDOW_H_INCLUDED
#define GRAPHWINDOW_H_INCLUDED

#include <QMainWindow>

class Graph;

class GraphWindow: public QMainWindow
{
    Q_OBJECT

    public:
        GraphWindow(QWidget* parent = nullptr);

    private:
        Graph* graph;
        int dt;

        void update();

    protected:
        void resizeEvent(QResizeEvent* event);
};

#endif
