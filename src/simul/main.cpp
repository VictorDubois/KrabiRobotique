#include <QApplication>
#include "simul/main.h"
#include "simul/main_window.h"
#include <ctime>

int main(int argc, char** argv)
{
	srand(time(NULL));

	QApplication app(argc, argv);
	MainWindow mw;
	mw.show();

	return app.exec();
}
