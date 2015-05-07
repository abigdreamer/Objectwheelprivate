#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "zdragdrop.h"
#include "zlayout.h"
#include "zdatabasemanager.h"
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>

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
		QVector<QWidget*> createdObjects;
	protected:
		bool eventFilter(QObject *obj, QEvent *event); //For drag&drop control

	public:
		ZLayout* lay; //For ZLayout
		void resizeEvent(QResizeEvent*); //For ZLayout control
		void createObjects(const QByteArray& jsonData);
		QByteArray generateObjects() const;
		void updateRecordList();
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
	};

#endif // MAINWINDOW_H
