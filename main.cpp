#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>
#include <QDesktopWidget>

/** !No changes! **/
int main(int argc, char *argv[])
	{
	QApplication a(argc, argv);
	LoginWindow d;
	d.move( QApplication::desktop()->availableGeometry().center() - d.rect().center() );
	d.show();

	return a.exec();
	}
