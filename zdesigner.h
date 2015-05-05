#ifndef ZDESIGNER_H
#define ZDESIGNER_H

#include <QObject>
#include "zlayout.h"
#include "zcouchbasemanager.h"
#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <QVector>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QByteArray>

#define MASTER_ID "masterRecord%1"
#define TEMP_ID "tempRecord%1"
#define CURRENT_ID "currentRecord"
class ZDesigner : public QObject
	{
		Q_OBJECT
	private:
		/// For creating object on MainWindow
		QMainWindow* mainWindow;
		/// For setting ZLayout for created object
		ZLayout* layout;
		/// For holding db and gui control times
		int dbControlMsec;
		int guiControlMsec;
		/// For controlling db and gui  for changing
		QTimer* dbController,* guiController;
		/// For holding backButton and forwardButton ( thats necessary for backing and forwarding all changes)
		QWidget* backButton,* forwardButton;
		/// For holding masterRecord lister
		QListWidget* masterRecordList;
		/// For holding host informations
		QString bucketAddress, bucketPassword;
		/// For managing Couchbase connections
		ZCouchbaseManager* cbManager;
		/// For holding last of tempRecord
		int sizeOfTemp;
		/// For holding last of masterRecord
		int sizeOfMaster;
		/// For controlling databese
		QByteArray oldHash;
		///For holding tempRecord
		QVector<QByteArray> tempRecords;
		///For holding masterRecord
		QVector<QByteArray> masterRecords;
		/// For holding created object
		QVector<QWidget*> createdObjects;

	public:
		explicit ZDesigner(QObject *parent = 0);
		/// For initializing necessary information
		void initSystem(QMainWindow* window, ZLayout* lay,
						QWidget* backBtn, QWidget* forwardBtn, QListWidget* mstRecList,
						const QString& bkAddr, const QString& bkPass,
						const int dbControlMs=1000, const int guiControlMs=1000);
		/// db and gui controlling was starting
		void startControlling();
		/// For loading data at first
		void loadData();
		/// For creating object from a json data to on mainwindow
		void createObjects(const QByteArray& jsonData);
		/// For setting current temp record to on couchbase server
		void setCurrentRecord(const int crtRecord );
		/// Getting current temp record from on couchbase server
		int getCurrentRecord();

		bool isDatabaseChanged();
		bool isGuiChanged();
		void hasDatabaseChanged();
		void hasGuiChanged();
	signals:

	public slots:
		void dbControl();
		void guiControl();
	};

#endif // ZDESIGNER_H
