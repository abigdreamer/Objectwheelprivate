#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "mainwindow.h"
#include <QMainWindow>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QByteArray>
#include <QFile>
#include <QDir>

namespace Ui {
	class LoginWindow;
	}

class LoginWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit LoginWindow(QWidget *parent = 0);
		~LoginWindow();
		void regulateWidgetGetometry(QWidget* widget);
		void regulateWidgetGetometryM(QWidget* widget);

	private slots:
		void on_forwardButton_clicked();

	private:
		Ui::LoginWindow *ui;
		QMessageBox err;
		MainWindow* mainScreen;
	};

#endif // LOGINWINDOW_H
