#include "MainWindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	Video* videoInstance = Video::getInstance();
	w.addObserver(videoInstance);
	w.show();
	return a.exec();
}
