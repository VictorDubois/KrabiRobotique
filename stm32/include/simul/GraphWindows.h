#ifndef GRAPHWINDOW_H_INCLUDED
#define GRAPHWINDOW_H_INCLUDED

#include <QMainWindow>
#include "simul/Graph.h"

class GraphWindows : public QMainWindow
{
public:
	virtual ~GraphWindows();
	GraphWindows();
private:
	Q_OBJECT

	Graph* graph;
    int dt;

private slots:
	void update();
protected:
	void resizeEvent(QResizeEvent* event);
};

#endif
