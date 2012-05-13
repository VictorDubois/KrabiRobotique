#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <QWidget>
#include <boost/circular_buffer.hpp>


class Graph : public QWidget
{
private:
	int dt;
	boost::circular_buffer<float> vLinear;
    boost::circular_buffer<float> vAngular;
public:
	Graph(QWidget* widget);
	virtual ~Graph();

	void update(int dt);
	void paintEvent(QPaintEvent* evt);
	void keyPressEvent(QKeyEvent* evt, bool press);

    static const int gWidth = 1000;
	static const int gHeight = 1000;
};

#endif

