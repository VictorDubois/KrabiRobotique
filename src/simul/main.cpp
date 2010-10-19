#include <QApplication>
#include "simul/main.h"
#include "simul/main_window.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	MainWindow mw;
	mw.show();

	return app.exec();
}
