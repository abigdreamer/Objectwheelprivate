#include "zdesigner.h"
#include <QDebug>

ZDesigner::ZDesigner(QObject *parent) :
	QObject(parent)
	{
	///Creating ZCouchbaseManager for managing connections
	cbManager=new ZCouchbaseManager;
	}

void ZDesigner::initSystem(QMainWindow* window, ZLayout* lay,
						   QWidget* backBtn, QWidget* forwardBtn, QListWidget* mstRecList,
						   const QString& bkAddr, const QString& bkPass,
						   const int dbControlMs, const int guiControlMs)
	{
	/// mainWindow for creating object on MainWindow
	mainWindow=window;
	/// layout for controlling ZLayout for created objects
	layout=lay;
	/// Dviding with two because each timer will start respectively
	/// Setting controllingTimers
	dbControlMsec=dbControlMs/2;
	guiControlMsec=guiControlMs/2;
	/// Holding back and forward button info for controlling enablable
	backButton=backBtn;
	forwardButton=forwardBtn;
	/// Holding master record list info for adding master records to that
	masterRecordList=mstRecList;
	/// Holding bucketAddress and bucketPassword
	bucketAddress=bkAddr;
	bucketPassword=bkPass;
	/// Creating controllor timers
	dbController= new QTimer(this);
	guiController= new QTimer(this);
	/// Connecting controllor timers to necessary funcs
	connect(dbController, SIGNAL(timeout()), this, SLOT(dbControl()));
	connect(guiController, SIGNAL(timeout()), this, SLOT(guiControl()));
	}

void ZDesigner::startControlling()
	{
	/// Starting controller timers

	if (sizeOfMaster>0)
		dbController->start(dbControlMsec);
	else
		qWarning("ZDesigner::startControlling() : Couldn't have any master record");

	}

void ZDesigner::loadData()
	{
	if (dbController->isActive())
		dbController->stop();
	if (guiController->isActive())
		guiController->stop();
	///Deleting objects for ZLayout which are created before.
	if (layout->size()>0)
		for (int i=0;i<createdObjects.size();i++)
			layout->removeWidgetOf(createdObjects.at(i));
	///Deleting objects which are created before.
	for (int i=0;i<createdObjects.size();i++)
		createdObjects.at(i)->close();
	/// Clearing created object list.
	if (createdObjects.size()>0)
		createdObjects.clear();
	sizeOfTemp=0;
	sizeOfMaster=0;
	tempRecords.clear();
	masterRecords.clear();
	masterRecordList->clear();
	/// connecting bucket with ZCouchbaseManager
	if (!cbManager->connectBucket(bucketAddress, bucketPassword))
		return;

	/// Learning last item of tempRecords
	sizeOfTemp=0;
	while(true)
		{
		if (*(cbManager->getData( QString(TEMP_ID).arg(sizeOfTemp) )) ==(QByteArray)NULL)
			break;
		sizeOfTemp++;
		}

	/// Learning last item of tempRecords
	sizeOfMaster=0;
	while(true)
		{
		if (*(cbManager->getData( QString(MASTER_ID).arg(sizeOfMaster) )) ==(QByteArray)NULL)
			break;
		sizeOfMaster++;
		}

	if (sizeOfMaster<1){
		qWarning("ZDesigner::startControlling() : Couldn't have any master record");
		return;
		}
	/// Loading tempRecords to memory
	for (int i=0;i<sizeOfMaster;i++){
		masterRecords.append(*(cbManager->getData( QString(MASTER_ID).arg(i) )));
		}

	/// Loading masterRecords to memory
	for (int i=0;i<sizeOfTemp;i++){
		tempRecords.append(*(cbManager->getData( QString(TEMP_ID).arg(i) )));
		}
	/// Loading master records to ListeWidget
	for (int i=0;i<sizeOfMaster;i++)
		masterRecordList->addItem(QString("Master Record %1").arg(i));
	/// Selecting last of master record
	if (sizeOfMaster>0)
		masterRecordList->setCurrentRow(sizeOfMaster-1);


	/// Creating a temp record with last item of master record if it isn't have.
	if (sizeOfTemp<1 && sizeOfMaster>0){
		tempRecords.append(masterRecords.last());
		sizeOfTemp++;
		this->setCurrentRecord(0);
		}

	/// Creating object on mainwindow
	if (sizeOfMaster>0)
		createObjects(tempRecords.last());

	}

void ZDesigner::createObjects(const QByteArray& jsonData)
	{
	///Deleting objects for ZLayout which are created before.
	if (layout->size()>0)
		for (int i=0;i<createdObjects.size();i++)
			layout->removeWidgetOf(createdObjects.at(i));
	///Deleting objects which are created before.
	for (int i=0;i<createdObjects.size();i++)
		createdObjects.at(i)->close();
	/// Clearing created object list.
	if (createdObjects.size()>0)
		createdObjects.clear();

	/// Getting json datas
	QJsonDocument loadDoc(QJsonDocument::fromJson(jsonData));
	QJsonObject allObjects = loadDoc.object();

	/// Iterating and creating all json object by ClassName
	for (int i=0;i<allObjects.size();i++)
		{
		const QJsonObject object = allObjects[QString("object%1").arg(i)].toObject();
		const QString& className = object["objectClass"].toString();

		if ( className == "QPushButton")
			{
			QPushButton* obj = new QPushButton(mainWindow);
			obj->setObjectName(object["objectName"].toString());
			obj->setText(object["text"].toString());
			obj->setEnabled(object["enabled"].toBool());
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());

			/// Adding object to createdObject
			createdObjects.append((QWidget*)obj);
			///  Showing object
			obj->show();
			/// Adding object to ZLayout
			layout->addItem(obj);

			}

		else if ( className == "QLineEdit")
			{
			QLineEdit* obj = new QLineEdit(mainWindow);
			obj->setObjectName(object["objectName"].toString());
			obj->setText(object["text"].toString());
			obj->setEnabled(object["enabled"].toBool());
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());
			/// Adding object to createdObject
			createdObjects.append((QWidget*)obj);
			///  Showing object
			obj->show();
			/// Adding object to ZLayout
			layout->addItem(obj);
			}

		else if ( className == "QComboBox")
			{
			QComboBox* obj = new QComboBox(mainWindow);
			obj->setObjectName(object["objectName"].toString());
			obj->setEnabled(object["enabled"].toBool());
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());
			/// Adding object to createdObject
			createdObjects.append((QWidget*)obj);
			///  Showing object
			obj->show();
			/// Adding object to ZLayout
			layout->addItem(obj);
			}

		else if ( className == "QLabel")
			{
			QLabel* obj = new QLabel(mainWindow);
			obj->setObjectName(object["objectName"].toString());
			obj->setText(object["text"].toString());
			obj->setEnabled(object["enabled"].toBool());
			if (object["picture"].toString()!="null" && object["picture"].toString()!="")
				obj->setPixmap(QPixmap(object["picture"].toString()).scaled(
							object["geometry"].toObject()["width"].toInt(),
						object["geometry"].toObject()["height"].toInt()));

			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());

			/// Adding object to createdObject
			createdObjects.append((QWidget*)obj);
			///  Showing object
			obj->show();
			/// Adding object to ZLayout
			layout->addItem(obj);
			}

		else if ( className == "QCheckBox")
			{
			QCheckBox* obj = new QCheckBox(mainWindow);
			obj->setObjectName(object["objectName"].toString());
			obj->setText(object["text"].toString());
			obj->setEnabled(object["enabled"].toBool());
			if (object["checked"].toBool())
				obj->setChecked(true);
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());

			/// Adding object to createdObject
			createdObjects.append((QWidget*)obj);
			///  Showing object
			obj->show();
			/// Adding object to ZLayout
			layout->addItem(obj);
			}

		else if ( className == "QMainWindow")
			{
			/*
			mainWindow->setWindowTitle(object["windowTitle"].toString());
			mainWindow->setEnabled(object["enabled"].toBool());

			mainWindow->centralWidget()->resize(object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());
			mainWindow->resize(object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());
			*/
			}
		}
	}

void ZDesigner::setCurrentRecord(const int crtRecord)
	{
	/// If currentRecord file is exist remove and set them
	if (cbManager->isIdExist(CURRENT_ID,bucketAddress,bucketPassword)){
		cbManager->removeData(CURRENT_ID);
		cbManager->setData(CURRENT_ID, QByteArray::number(crtRecord));
		}
	else /// otherwise only set currentRecord
		cbManager->setData(CURRENT_ID,QByteArray::number(crtRecord));
	}

int ZDesigner::getCurrentRecord()
	{
	/// get currentRecord number and return it, if it is exist.
	if (cbManager->isIdExist(CURRENT_ID,bucketAddress,bucketPassword)){
		return cbManager->getData(CURRENT_ID)->toInt();
		}
	else /// otherwise return -1
		return -1;
	}

bool ZDesigner::isDatabaseChanged()
	{
	/*
	/// connecting bucket with ZCouchbaseManager
	if (!cbManager->connectBucket(bucketAddress, bucketPassword))
		return false;

	if (dbController->isActive())
		dbController->stop();
	if (guiController->isActive())
		guiController->stop();
	///Deleting objects for ZLayout which are created before.
	if (layout->size()>0)
		for (int i=0;i<createdObjects.size();i++)
			layout->removeWidgetOf(createdObjects.at(i));
	///Deleting objects which are created before.
	for (int i=0;i<createdObjects.size();i++)
		createdObjects.at(i)->close();
	/// Clearing created object list.
	if (createdObjects.size()>0)
		createdObjects.clear();
	sizeOfTemp=0;
	sizeOfMaster=0;
	currentRecord=0;
	tempRecords.clear();
	masterRecords.clear();
	masterRecordList->clear();
	/// connecting bucket with ZCouchbaseManager
	if (!cbManager->connectBucket(bucketAddress, bucketPassword))
		return;

	/// Learning last item of tempRecords
	sizeOfTemp=0;
	while(true)
		{
		if (*(cbManager->getData( QString(TEMP_ID).arg(sizeOfTemp) )) ==NULL)
			break;
		sizeOfTemp++;
		}

	/// Learning last item of tempRecords
	sizeOfMaster=0;
	while(true)
		{
		if (*(cbManager->getData( QString(MASTER_ID).arg(sizeOfMaster) )) ==NULL)
			break;
		sizeOfMaster++;
		}

	if (sizeOfMaster<1){
		qWarning("ZDesigner::startControlling() : Couldn't have any master record");
		return;
		}
	/// Loading tempRecords to memory
	for (int i=0;i<sizeOfMaster;i++){
		masterRecords.append(*(cbManager->getData( QString(MASTER_ID).arg(i) )));
		}
	//qDebug() << *(cbManager->getData( QString(MASTER_ID).arg(0) ));
	/// Loading masterRecords to memory
	for (int i=0;i<sizeOfTemp;i++){
		tempRecords.append(*(cbManager->getData( QString(TEMP_ID).arg(i) )));
		}

*/
	QFile loadFile("objects.json");
	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Couldn't open objects file.");
		return false;
		}
	QByteArray docData = loadFile.readAll();

	if ( !(oldHash == QCryptographicHash::hash(docData, QCryptographicHash::Md5)) )
		{
		oldHash = QCryptographicHash::hash(docData, QCryptographicHash::Md5);
		return true;
		}
	return false;
	}

bool ZDesigner::isGuiChanged()
	{
	return false;
	}

void ZDesigner::hasDatabaseChanged()
	{
	/*
	for (int i=0;i<createdWidgets.size();i++)
		createdWidgets.at(i)->close();
	createdWidgets.clear();
	lay->clearItem();
	lay->addItem(ui->backButton);
	lay->addItem(ui->forwardButton);

	QByteArray docData = loadFile.readAll();
	QJsonDocument loadDoc(QJsonDocument::fromJson(docData));
	QJsonObject allObjects = loadDoc.object();
	for (int i=0;i<allObjects.size();i++)
		{
		QJsonObject object = allObjects[QString("object%1").arg(i)].toObject();
		createObject(object["objectClass"].toString(), object);
		}
*/

	}

void ZDesigner::hasGuiChanged()
	{

	}

void ZDesigner::dbControl()
	{
	dbController->stop();

	/// Controlling db for changing
	if (this->isDatabaseChanged() )
		hasDatabaseChanged();
	else
		layout->updateWidgets(); /// Look That!!!! (or that Will maybe in guiControl)
	guiController->start(guiControlMsec);
	}

void ZDesigner::guiControl()
	{
	guiController->stop();

	// ...

	dbController->start(dbControlMsec);
	}
