#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug> // For testing
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
	{
	ui->setupUi(this);

	/** !DragDrop! **/
	//Creating dragger
	dragger = new ZDragDrop(this);
	dragger->setObjectList(&createdObjects);


	lay = new ZLayout;
	lay->setAspectRatioProtected(true);
	connect(this,SIGNAL(resEvent()),lay,SLOT(updateWidgets()));
	dragger->setLay(lay);
	//For eventFilter
	qApp->installEventFilter(this);
	//Adding without object to dragger
	dragger->addWithoutObject(ui->backButton);

	dragger->addWithoutObject(ui->frame_2);
	dragger->addWithoutObject(ui->frame_3);

	dragger->addWithoutObject(ui->forwardButton);
	dragger->addWithoutObject(ui->saveButton);
	dragger->addWithoutObject(ui->masterRecordList);
	dragger->addWithoutObject(ui->deleteTempButton);
	dragger->addWithoutObject(ui->loadMasterButton);
	dragger->addWithoutObject(ui->deleteTempButton);

	dragger->addWithoutObject(ui->label_6);
	dragger->addWithoutObject(ui->widget);
	dragger->addWithoutObject(this);
	dragger->addWithoutObject(ui->centralWidget);
	}

MainWindow::~MainWindow()
	{
	delete ui;
	}

void MainWindow::databaseChangeHandler()
	{ this->createObjects(databaseManager->getFile()); updateRecordList(); }

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
	{
	/** !DragDrop! **/
	//Calling dragger
	return dragger->updateWidget(event,ui,this,obj);
	}

void MainWindow::createObjects(const QByteArray& jsonData)
	{

	lay->clearAllItem();
	for (int i=0;i<createdObjects.size();i++)
		createdObjects.at(i)->close();

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
			QPushButton* obj = new QPushButton(ui->widget);
			obj->setObjectName(object["objectName"].toString());
			obj->setText(object["text"].toString());
			obj->setEnabled(object["enabled"].toBool());
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());

			createdObjects.append(obj);
			///  Showing object
			obj->show();
			/// Adding object to ZLayout
			lay->addItem(obj);
			obj->setStyleSheet("background-color:transparent;");
			}

		else if ( className == "QLineEdit")
			{
			QLineEdit* obj = new QLineEdit(ui->widget);
			obj->setObjectName(object["objectName"].toString());
			obj->setText(object["text"].toString());
			obj->setEnabled(object["enabled"].toBool());
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());

			QPalette palette = obj->palette();
			palette.setColor(obj->foregroundRole(), qRgb(255,255,255));
			obj->setPalette(palette);

			/// Adding object to createdObject
			createdObjects.append(obj);
			///  Showing object
			obj->show();
			/// Adding object to ZLayout
			lay->addItem(obj);
			obj->setStyleSheet("border-image:url(:/pics/plain.png);");
			}

		else if ( className == "QComboBox")
			{
			QComboBox* obj = new QComboBox(ui->widget);
			obj->setObjectName(object["objectName"].toString());
			obj->setEnabled(object["enabled"].toBool());
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());
			/// Adding object to createdObject
			createdObjects.append(obj);
			///  Showing object
			obj->show();
			/// Adding object to ZLayout
			lay->addItem(obj);
			//obj->setStyleSheet("background-color:transparent;");
			}

		else if ( className == "QLabel")
			{
			QLabel* obj = new QLabel(ui->widget);
			obj->setObjectName(object["objectName"].toString());
			obj->setText(object["text"].toString());
			obj->setEnabled(object["enabled"].toBool());
			if (object["picture"].toString()!="null" && object["picture"].toString()!="")
				obj->setStyleSheet(QString("border-image: url(%1);").arg(object["picture"].toString()));
			else
				obj->setStyleSheet("background:transparent;");
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());

			QPalette palette = obj->palette();
			palette.setColor(obj->foregroundRole(), qRgba(object["color"].toObject()["r"].toInt(),
					object["color"].toObject()["g"].toInt(),
					object["color"].toObject()["b"].toInt(),
					object["color"].toObject()["a"].toInt()));
			obj->setPalette(palette);
			/// Adding object to createdObject
			createdObjects.append(obj);
			///  Showing object
			obj->show();
			/// Adding object to ZLayout
			lay->addItem(obj);
			}

		else if ( className == "QCheckBox")
			{
			QCheckBox* obj = new QCheckBox(ui->widget);
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
			createdObjects.append(obj);
			///  Showing object
			obj->show();
			/// Adding object to ZLayout
			lay->addItem(obj);
			obj->setStyleSheet("background-color:transparent;");
			}
		else if ( className == "QWidget")
			{
			QWidget* obj = new QWidget(ui->widget);
			obj->setObjectName(object["objectName"].toString());
			obj->setGeometry(obj->x(),
					obj->y(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());

			/// Adding object to createdObject
			createdObjects.append(obj);
			///  Showing object
			obj->show();
			/// Adding object to ZLayout
			lay->initMainWidgets(ui->widget,obj);
			obj->lower();
			obj->setStyleSheet("background-color:transparent;");
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
	this->resizeEvent(0);
	}

QByteArray MainWindow::generateObjects() const
	{
	QJsonDocument jsonDoc;
	QJsonObject mainObject;

	for (int i=0;i<createdObjects.size();i++)
		{
		const QString& className = createdObjects.at(i)->metaObject()->className();

		if ( className == "QPushButton")
			{
			QPushButton* obj = reinterpret_cast<QPushButton*>(createdObjects.at(i));

			QJsonObject geometry;
			geometry.insert("x",obj->x());
			geometry.insert("y",obj->y());
			geometry.insert("width",obj->width());
			geometry.insert("height",obj->height());

			QJsonObject object;
			object.insert("objectClass",className);
			object.insert("objectName",obj->objectName());
			object.insert("text",obj->text());
			object.insert("enabled",obj->isEnabled());
			object.insert("geometry",geometry);

			mainObject.insert(QString("object%1").arg(i),object);
			}

		else if ( className == "QLineEdit")
			{
			QLineEdit* obj = reinterpret_cast<QLineEdit*>(createdObjects.at(i));

			QJsonObject geometry;
			geometry.insert("x",obj->x());
			geometry.insert("y",obj->y());
			geometry.insert("width",obj->width());
			geometry.insert("height",obj->height());

			QJsonObject object;
			object.insert("objectClass",className);
			object.insert("objectName",obj->objectName());
			object.insert("text",obj->text());
			object.insert("enabled",obj->isEnabled());
			object.insert("geometry",geometry);

			mainObject.insert(QString("object%1").arg(i),object);
			}

		else if ( className == "QComboBox")
			{
			QComboBox* obj = reinterpret_cast<QComboBox*>(createdObjects.at(i));

			QJsonObject geometry;
			geometry.insert("x",obj->x());
			geometry.insert("y",obj->y());
			geometry.insert("width",obj->width());
			geometry.insert("height",obj->height());

			QJsonObject object;
			object.insert("objectClass",className);
			object.insert("objectName",obj->objectName());
			object.insert("enabled",obj->isEnabled());
			object.insert("geometry",geometry);

			mainObject.insert(QString("object%1").arg(i),object);
			}

		else if ( className == "QLabel")
			{
			QLabel* obj = reinterpret_cast<QLabel*>(createdObjects.at(i));

			QJsonObject geometry;
			geometry.insert("x",obj->x());
			geometry.insert("y",obj->y());
			geometry.insert("width",obj->width());
			geometry.insert("height",obj->height());

			QJsonObject color;
			QRgb rgb = obj->palette().foreground().color().rgba();
			color.insert("r",qRed(rgb));
			color.insert("g",qGreen(rgb));
			color.insert("b",qBlue(rgb));
			color.insert("a",qAlpha(rgb));

			QJsonObject object;
			object.insert("objectClass",className);
			object.insert("objectName",obj->objectName());
			object.insert("text",obj->text());
			object.insert("enabled",obj->isEnabled());
			if (!obj->styleSheet().isNull())
				{
				QString sheet;
				if (obj->styleSheet().split("url(").size()>1)
					sheet= obj->styleSheet().split("url(").at(1);
				sheet.remove(")");
				sheet.remove(";");
				object.insert("picture",sheet);
				}
			else
				object.insert("picture","");

			object.insert("geometry",geometry);
			object.insert("color",color);
			mainObject.insert(QString("object%1").arg(i),object);

			}

		else if ( className == "QCheckBox")
			{
			QCheckBox* obj = reinterpret_cast<QCheckBox*>(createdObjects.at(i));

			QJsonObject geometry;
			geometry.insert("x",obj->x());
			geometry.insert("y",obj->y());
			geometry.insert("width",obj->width());
			geometry.insert("height",obj->height());

			QJsonObject object;
			object.insert("objectClass",className);
			object.insert("objectName",obj->objectName());
			object.insert("text",obj->text());
			object.insert("enabled",obj->isEnabled());
			object.insert("checked",obj->isChecked());
			object.insert("geometry",geometry);

			mainObject.insert(QString("object%1").arg(i),object);

			}
		else if ( className == "QWidget")
			{
			QWidget* obj = reinterpret_cast<QWidget*>(createdObjects.at(i));

			QJsonObject geometry;
			geometry.insert("width",obj->width());
			geometry.insert("height",obj->height());

			QJsonObject object;
			object.insert("objectClass",className);
			object.insert("objectName",obj->objectName());
			object.insert("geometry",geometry);

			mainObject.insert(QString("object%1").arg(i),object);

			}

		else if ( className == "QMainWindow")
			{
			/* ... */
			}
		}
	jsonDoc.setObject(mainObject);
	return jsonDoc.toJson();
	}

void MainWindow::updateRecordList()
	{
	int sz=databaseManager->getSize();
	ui->masterRecordList->clear();
	for (int i=0;i<sz;i++)
		{
		ui->masterRecordList->addItem(QString("Record-%1").arg(i));
		}
	ui->masterRecordList->setCurrentRow(databaseManager->getCurrentFileIndex());
	}

void MainWindow::setDatabaseFolderName(const QString& name)
	{
	QFile* fil= new QFile;
	fil->setFileName(":/objectRecord0.json");
	if (!fil->open(QIODevice::ReadOnly))
		return;
	QByteArray buff = fil->readAll();
	fil->close();

	fil->setFileName(QDir::currentPath()+"/"+name + "/objectRecord0.json");
	if (!fil->open(QIODevice::WriteOnly))
		return;
	fil->write(buff);
	fil->close();

	databaseManager = new ZDatabaseManager;
	databaseManager->setCheckTimeout(1000);
	databaseManager->setFileName(QDir::currentPath()+"/"+name,"objectRecord");
	connect(databaseManager,SIGNAL(databaseChanged()),this,SLOT(databaseChangeHandler()));
	databaseManager->startChangeListener();
	}


void MainWindow::on_saveButton_clicked()
	{ databaseManager->addFile(generateObjects()); updateRecordList(); }

void MainWindow::on_backButton_clicked()
	{
	int backIndex = databaseManager->getCurrentFileIndex()-1;
	if ( backIndex >= 0 )
		databaseManager->setCurrentFileIndex(backIndex);
	}

void MainWindow::on_forwardButton_clicked()
	{
	int nextIndex = databaseManager->getCurrentFileIndex()+1;
	if (nextIndex < databaseManager->getSize() )
		databaseManager->setCurrentFileIndex(nextIndex);
	}

void MainWindow::on_deleteTempButton_clicked()
	{ databaseManager->removeFile(); }

void MainWindow::on_loadMasterButton_clicked()
	{ databaseManager->setCurrentFileIndex(ui->masterRecordList->currentRow()); }
void MainWindow::resizeEvent(QResizeEvent *)
	{
	/** !Layout! **/
	//Calling ZLayout
	emit resEvent();
	}
