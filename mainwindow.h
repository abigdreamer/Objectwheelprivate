#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "zdragdrop.h"
#include "zlayout.h"
#include "zdatabasemanager.h"
#include "zwebbrowser.h"
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>
#include <QDesktopWidget>

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
		ZLayout* lay;
		ZDatabaseManager* databaseManager;
		QVector<QWidget*> createdObjects;
	protected:
		bool eventFilter(QObject *obj, QEvent *event); //For drag&drop control

	public:
		void resizeEvent(QResizeEvent*); //For ZLayout control
		void createObjects(const QByteArray& jsonData);
		QByteArray generateObjects() const;
		void updateRecordList();
		void setDatabaseFolderName(const QString& name);
		void regulateWidgetGetometry(QWidget* widget);
		void regulateWidgetGetometryM(QWidget* widget, int exSize=2.0);
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
	public slots:

	signals:
		void resEvent() const; //For ZLayout control
	private slots:
		void databaseChangeHandler();
		void on_saveButton_clicked();
		void on_backButton_clicked();
		void on_forwardButton_clicked();
		void on_deleteTempButton_clicked();
		void on_loadMasterButton_clicked();

		void on_tabButton_clicked();
		void on_tabButton_2_clicked();
		void on_tabButton_3_clicked();
		void on_pushButton_3_clicked();
		void on_pushButton_2_clicked();
		void on_pushButton_4_clicked();
		void on_pushButton_clicked();
		void on_pushButton_6_clicked();
		void on_pushButton_5_clicked();
		void on_pushButton_7_clicked();
		void on_pushButton_8_clicked();
	};

#endif // MAINWINDOW_H
