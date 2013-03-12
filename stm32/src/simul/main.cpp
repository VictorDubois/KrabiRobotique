#include <QApplication>
#include "simul/main.h"
#include "simul/main_window.h"
#include "simul/GraphWindows.h"
#include <ctime>

#undef STM32F10X_CL // pour le simulateur, parce que un des fichiers définit cette macro et ne devrait pas. a commenter lors de la compil

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
