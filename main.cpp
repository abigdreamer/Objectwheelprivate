#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>

/** !No changes! **/
int main(int argc, char *argv[])
	{
	QApplication a(argc, argv);
	LoginWindow d;
	d.show();

	return a.exec();
	}
