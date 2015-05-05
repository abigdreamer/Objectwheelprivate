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
	signals:
		void resEvent() const; //For ZLayout control
	private slots:
		void on_backButton_clicked();
		void on_forwardButton_clicked();
		void on_getButton_clicked();
		void on_loadMasterButton_clicked();
	};

#endif // MAINWINDOW_H
