#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "zdragdrop.h"
#include "zlayout.h"
#include "zdesigner.h"

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
		ZDesigner* designer; //For design

	protected:
		bool eventFilter(QObject *obj, QEvent *event); //For drag&drop control

	public:
		ZLayout* lay; //For ZLayout
		void resizeEvent(QResizeEvent*); //For ZLayout control

		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
	public slots:
		void on_getButton_clicked();
	signals:
		void resEvent() const; //For ZLayout control
	private slots:

	};

#endif // MAINWINDOW_H
