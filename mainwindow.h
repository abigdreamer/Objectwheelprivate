#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "zdragdrop.h"
#include "zlayout.h"
#include "zdatabasemanager.h"

namespace Ui
	{
	class MainWindow;
	}

class MainWindow : public QMainWindow
	{
		Q_OBJECT

	private:
		Ui::MainWindow *ui;
		ZDragDrop* dragger; //For drag&drop
		ZDatabaseManager* databaseManager;
	protected:
		bool eventFilter(QObject *obj, QEvent *event); //For drag&drop control

	public:
		ZLayout* lay; //For ZLayout
		void resizeEvent(QResizeEvent*); //For ZLayout control

		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
	public slots:

	signals:
		void resEvent() const; //For ZLayout control
	private slots:
		void databaseChangeHandler();
	};

#endif // MAINWINDOW_H
