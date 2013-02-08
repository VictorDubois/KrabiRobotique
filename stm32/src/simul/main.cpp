#include <QApplication>
#include "simul/main.h"
#include "simul/main_window.h"
#include "simul/GraphWindows.h"
#include <ctime>


int main(int argc, char** argv)
{
	srand(42);

	QApplication app(argc, argv);
	MainWindow mw;
	mw.show();

	//GraphWindows gw;
	//gw.show();

	return app.exec();
}
