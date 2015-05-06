#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug> // For testing
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
	{
	ui->setupUi(this);

	/** !DragDrop! **/
	//Creating dragger
	dragger = new ZDragDrop;
	//For eventFilter
	qApp->installEventFilter(this);
	//Adding without object to dragger
	dragger->addWithoutObject(ui->backButton);
	dragger->addWithoutObject(ui->forwardButton);
	dragger->addWithoutObject(ui->optionsLine);
	dragger->addWithoutObject(ui->saveButton);
	dragger->addWithoutObject(ui->toolBox);
	dragger->addWithoutObject(ui->masterBox);
	dragger->addWithoutObject(ui->masterRecordList);
	dragger->addWithoutObject(ui->widgetBox);
	dragger->addWithoutObject(ui->buttonPage);
	dragger->addWithoutObject(ui->containerPage);
	dragger->addWithoutObject(ui->inputPage);
	dragger->addWithoutObject(ui->toolboxLine);
	dragger->addWithoutObject(ui->hortLine);
	dragger->addWithoutObject(ui->vertLine);
	dragger->addWithoutObject(ui->deleteTempButton);
	dragger->addWithoutObject(ui->loadMasterButton);
	dragger->addWithoutObject(ui->deleteMasterButton);
	dragger->addWithoutObject(ui->deleteTempButton);
	dragger->addWithoutObject(ui->designTitle);

	/** !Layout! **/
	//Creating ZLayout and connecting resizeEvent
	lay = new ZLayout;
	connect(this,SIGNAL(resEvent()),lay,SLOT(updateWidgets()));
	//Initing centralWidget and widget to ZLayout for controllig widgets
	lay->initMainWidgets(ui->centralWidget,ui->widget);
	//Adding stabile object to ZLayout(ing)
	lay->addItem(ui->backButton);
	lay->addItem(ui->forwardButton);
	lay->addItem(ui->optionsLine);
	lay->addItem(ui->saveButton);
	lay->addItem(ui->masterBox);
	lay->addItem(ui->toolBox);
	lay->addItem(ui->masterRecordList);
	lay->addItem(ui->widgetBox);
	lay->addItem(ui->buttonPage);
	lay->addItem(ui->containerPage);
	lay->addItem(ui->inputPage);
	lay->addItem(ui->toolboxLine);
	lay->addItem(ui->hortLine);
	lay->addItem(ui->vertLine);
	lay->addItem(ui->deleteTempButton);
	lay->addItem(ui->loadMasterButton);
	lay->addItem(ui->deleteMasterButton);
	lay->addItem(ui->deleteTempButton);
	lay->addItem(ui->designTitle);

	databaseManager = new ZDatabaseManager;
	databaseManager->setCheckTimeout(1000);
	databaseManager->setFileName("..","objectRecord");
	connect(databaseManager,SIGNAL(databaseChanged()),this,SLOT(databaseChangeHandler()));
	databaseManager->startChangeListener();

	}

MainWindow::~MainWindow()
	{
	delete ui;
	}

void MainWindow::databaseChangeHandler()
	{

	this->createObjects(databaseManager->getFile());

	}

bool MainWindow::eventFilter(QObject*, QEvent* event)
	{
	/** !DragDrop! **/
	//Calling dragger
	return dragger->updateWidget(event,ui,this);
	}

void MainWindow::resizeEvent(QResizeEvent *)
	{
	/** !Layout! **/
	//Calling ZLayout
	emit resEvent();
	}

void MainWindow::createObjects(const QByteArray& jsonData)
	{

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
			QPushButton* obj = new QPushButton(this);
			obj->setObjectName(object["objectName"].toString());
			obj->setText(object["text"].toString());
			obj->setEnabled(object["enabled"].toBool());
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());

			///  Showing object
			obj->show();
			/// Adding object to ZLayout

			}

		else if ( className == "QLineEdit")
			{
			QLineEdit* obj = new QLineEdit(this);
			obj->setObjectName(object["objectName"].toString());
			obj->setText(object["text"].toString());
			obj->setEnabled(object["enabled"].toBool());
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());
			/// Adding object to createdObject

			///  Showing object
			obj->show();
			/// Adding object to ZLayout

			}

		else if ( className == "QComboBox")
			{
			QComboBox* obj = new QComboBox(this);
			obj->setObjectName(object["objectName"].toString());
			obj->setEnabled(object["enabled"].toBool());
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());
			/// Adding object to createdObject

			///  Showing object
			obj->show();
			/// Adding object to ZLayout

			}

		else if ( className == "QLabel")
			{
			QLabel* obj = new QLabel(this);
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

			///  Showing object
			obj->show();
			/// Adding object to ZLayout

			}

		else if ( className == "QCheckBox")
			{
			QCheckBox* obj = new QCheckBox(this);
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

			///  Showing object
			obj->show();
			/// Adding object to ZLayout

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

