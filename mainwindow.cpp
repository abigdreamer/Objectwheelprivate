#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug> // For testing
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QDir>
#include <QFrame>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWebView>
#include <QProgressBar>

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
			QFont fnt("Arial",8);
			obj->setFont(fnt);
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
			QFont fnt("Arial",8);
			obj->setFont(fnt);
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
			QFont fnt("Arial",8);
			obj->setFont(fnt);
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
			QFont fnt("Arial",8);
			obj->setFont(fnt);
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
			QFont fnt("Arial",8);
			obj->setFont(fnt);
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

		else if ( className == "QWebView")
			{
			QFrame* obj = new QFrame(ui->widget);
			obj->setObjectName(object["objectName"].toString());
			obj->setEnabled(object["enabled"].toBool());
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());
			obj->setStyleSheet(QString("#%1 {"
									   "border: 1px solid rgba(255,255,255,150);"
									   "border-radius: 5px;"
									   "background-color: rgba(0, 0, 0, 140);}").arg(object["objectName"].toString()));
			obj->setFrameShape(QFrame::Box);
			obj->setFrameShadow(QFrame::Plain);

			QGridLayout *gridLayout_2;
			QVBoxLayout *verticalLayout_2;
			QFrame *frame_4;
			QHBoxLayout *horizontalLayout_4;
			QPushButton *pushButton_2;
			QPushButton *pushButton_3;
			QLineEdit *lineEdit;
			QPushButton *pushButton;
			QPushButton *pushButton_5;
			QPushButton *pushButton_4;
			QFrame *frame_5;
			QVBoxLayout *verticalLayout_3;
			QWebView *webView;
			QProgressBar *progressBar;


			gridLayout_2 = new QGridLayout(obj);
			gridLayout_2->setSpacing(5);
			gridLayout_2->setContentsMargins(11, 11, 11, 11);
			gridLayout_2->setObjectName(QString("gridLayout_2%1").arg(object["objectName"].toString()));
			gridLayout_2->setContentsMargins(9, 9, 9, 9);
			verticalLayout_2 = new QVBoxLayout();
			verticalLayout_2->setSpacing(6);
			verticalLayout_2->setObjectName(QString("verticalLayout_2%1").arg(object["objectName"].toString()));
			frame_4 = new QFrame(obj);
			frame_4->setObjectName(QString("frame_4%1").arg(object["objectName"].toString()));
			frame_4->setStyleSheet(QString("#frame_4%1 {\n"
										   "border: 1px solid rgba(255,255,255,150);\n"
										   "border-radius: 5px;\n"
										   "background-color: rgba(0, 0, 0, 60);\n"
										   "}").arg(object["objectName"].toString()));


			frame_4->setFrameShape(QFrame::Box);
			frame_4->setFrameShadow(QFrame::Plain);
			horizontalLayout_4 = new QHBoxLayout(frame_4);
			horizontalLayout_4->setSpacing(0);
			horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
			horizontalLayout_4->setObjectName(QString("horizontalLayout_4%1").arg(object["objectName"].toString()));
			horizontalLayout_4->setContentsMargins(2, 2, 2, 2);
			pushButton_2 = new QPushButton(frame_4);
			pushButton_2->setObjectName(QString("pushButton_2%1").arg(object["objectName"].toString()));
			QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			sizePolicy.setHorizontalStretch(0);
			sizePolicy.setVerticalStretch(0);
			sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
			pushButton_2->setSizePolicy(sizePolicy);
			pushButton_2->setMinimumSize(QSize(27, 27));
			pushButton_2->setMaximumSize(QSize(27, 27));
			pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
			pushButton_2->setStyleSheet(QString("QPushButton#pushButton_2%1 {\n"
												"   border-image: url(:/pics/back.png);\n"
												" }\n"
												"QPushButton#pushButton_2%1:pressed {\n"
												"   border-image: url(:/pics/back2.png);\n"
												" }\n"
												"").arg(object["objectName"].toString()));

			horizontalLayout_4->addWidget(pushButton_2);

			pushButton_3 = new QPushButton(frame_4);
			pushButton_3->setObjectName(QString("pushButton_3%1").arg(object["objectName"].toString()));
			sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
			pushButton_3->setSizePolicy(sizePolicy);
			pushButton_3->setMinimumSize(QSize(27, 27));
			pushButton_3->setMaximumSize(QSize(27, 27));
			pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));
			pushButton_3->setStyleSheet(QString("QPushButton#pushButton_3%1{\n"
												"   border-image: url(:/pics/forward.png);\n"
												" }\n"
												"QPushButton#pushButton_3%1:pressed {\n"
												"   border-image: url(:/pics/forward2.png);\n"
												" }").arg(object["objectName"].toString()));

			horizontalLayout_4->addWidget(pushButton_3);

			lineEdit = new QLineEdit(frame_4);
			lineEdit->setObjectName(QString("lineEdit%1").arg(object["objectName"].toString()));
			lineEdit->setMaximumSize(QSize(16777215, 27));
			lineEdit->setText("http://www.google.com.tr");
			QFont font;
			font.setBold(false);
			font.setWeight(50);
			font.setStrikeOut(false);
			font.setKerning(true);
			lineEdit->setFont(font);
			lineEdit->setStyleSheet(QString("#lineEdit%1 {\n"
											"border: 1px solid rgba(255,255,255,150);\n"
											"border-radius: 5px;\n"
											"background-color: rgba(0, 0, 0, 60);\n"
											"color:rgb(255,255,255)\n"
											"}").arg(object["objectName"].toString()));

			horizontalLayout_4->addWidget(lineEdit);

			pushButton = new QPushButton(frame_4);
			pushButton->setObjectName(QString("pushButton%1").arg(object["objectName"].toString()));
			sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
			pushButton->setSizePolicy(sizePolicy);
			pushButton->setMinimumSize(QSize(27, 27));
			pushButton->setMaximumSize(QSize(27, 27));
			pushButton->setCursor(QCursor(Qt::PointingHandCursor));
			pushButton->setStyleSheet(QString("QPushButton#pushButton%1 {\n"
											  "   border-image: url(:/pics/go.png);\n"
											  " }\n"
											  "QPushButton#pushButton%1:pressed {\n"
											  "   border-image: url(:/pics/go2.png);\n"
											  " }").arg(object["objectName"].toString()));

			horizontalLayout_4->addWidget(pushButton);

			pushButton_5 = new QPushButton(frame_4);
			pushButton_5->setObjectName(QString("pushButton_5%1").arg(object["objectName"].toString()));
			sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
			pushButton_5->setSizePolicy(sizePolicy);
			pushButton_5->setMinimumSize(QSize(27, 27));
			pushButton_5->setMaximumSize(QSize(27, 27));
			pushButton_5->setCursor(QCursor(Qt::PointingHandCursor));
			pushButton_5->setStyleSheet(QString("QPushButton#pushButton_5%1 {\n"
												"   border-image: url(:/pics/exit.png);\n"
												" }\n"
												"QPushButton#pushButton_5%1:pressed {\n"
												"   border-image: url(:/pics/exit2.png);\n"
												" }").arg(object["objectName"].toString()));

			horizontalLayout_4->addWidget(pushButton_5);

			pushButton_4 = new QPushButton(frame_4);
			pushButton_4->setObjectName(QString("pushButton_4%1").arg(object["objectName"].toString()));
			sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
			pushButton_4->setSizePolicy(sizePolicy);
			pushButton_4->setMinimumSize(QSize(27, 27));
			pushButton_4->setMaximumSize(QSize(27, 27));
			pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));
			pushButton_4->setStyleSheet(QString("QPushButton#pushButton_4%1 {\n"
												"   border-image: url(:/pics/reload.png);\n"
												" }\n"
												"QPushButton#pushButton_4%1:pressed {\n"
												"   border-image: url(:/pics/reload2.png);\n"
												" }").arg(object["objectName"].toString()));

			horizontalLayout_4->addWidget(pushButton_4);


			verticalLayout_2->addWidget(frame_4);

			frame_5 = new QFrame(obj);
			frame_5->setObjectName(QString("frame_5%1").arg(object["objectName"].toString()));
			frame_5->setStyleSheet(QString("#frame_3%1 {\n"
										   "border: 1px solid rgba(0,0,0,150);\n"
										   "border-radius: 5px;\n"
										   "background-color: rgba(0, 0, 0, 60);\n"
										   "}").arg(object["objectName"].toString()));
			frame_5->setFrameShape(QFrame::StyledPanel);
			frame_5->setFrameShadow(QFrame::Raised);
			verticalLayout_3 = new QVBoxLayout(frame_5);
			verticalLayout_3->setSpacing(1);
			verticalLayout_3->setContentsMargins(11, 11, 11, 11);
			verticalLayout_3->setObjectName(QString("verticalLayout_3%1").arg(object["objectName"].toString()));
			verticalLayout_3->setContentsMargins(1, 1, 1, 1);
			webView = new QWebView(frame_5);
			webView->setObjectName(QString("webView%1").arg(object["objectName"].toString()));
			QPalette palette;
			QBrush brush(QColor(96, 96, 96, 255));
			brush.setStyle(Qt::SolidPattern);
			palette.setBrush(QPalette::Active, QPalette::Base, brush);
			palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
			QBrush brush1(QColor(0, 0, 0, 60));
			brush1.setStyle(Qt::SolidPattern);
			palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
			webView->setPalette(palette);
			webView->setStyleSheet(QString("%1").arg(object["objectName"].toString()));
			webView->setUrl(QUrl(QStringLiteral("about:blank")));

			verticalLayout_3->addWidget(webView);


			verticalLayout_2->addWidget(frame_5);

			progressBar = new QProgressBar(obj);
			progressBar->setObjectName(QString("progressBar%1").arg(object["objectName"].toString()));
			progressBar->setValue(0);

			verticalLayout_2->addWidget(progressBar);
			gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

			QObject::connect(pushButton_2, SIGNAL(clicked()), webView, SLOT(back()));
			QObject::connect(pushButton_3, SIGNAL(clicked()), webView, SLOT(forward()));
			QObject::connect(pushButton_5, SIGNAL(clicked()), webView, SLOT(stop()));
			QObject::connect(pushButton_4, SIGNAL(clicked()), webView, SLOT(reload()));
			QObject::connect(pushButton, SIGNAL(clicked()), this, SLOT(goButtonClicked()));
			connect(webView, SIGNAL(loadProgress(int)),progressBar,SLOT(setValue(int)));
			//connect(webView, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

			dragger->addWithoutObject(frame_4);
			dragger->addWithoutObject(frame_5);
			dragger->addWithoutObject(pushButton);
			dragger->addWithoutObject(pushButton_2);
			dragger->addWithoutObject(pushButton_3);
			dragger->addWithoutObject(pushButton_4);
			dragger->addWithoutObject(pushButton_5);
			dragger->addWithoutObject(lineEdit);
			dragger->addWithoutObject(webView);
			dragger->addWithoutObject(progressBar);

			createdObjects.append(obj);

			///  Showing object
			obj->show();
			QFont fnt("Arial",8);
			obj->setFont(fnt);
			/// Adding object to ZLayout
			lay->addItem(obj);

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
		else if ( className == "QFrame")
			{

			QFrame* obj = reinterpret_cast<QFrame*>(createdObjects.at(i));

			QJsonObject geometry;
			geometry.insert("x",obj->x());
			geometry.insert("y",obj->y());
			geometry.insert("width",obj->width());
			geometry.insert("height",obj->height());

			QJsonObject object;
			object.insert("objectClass","QWebView");
			object.insert("objectName",obj->objectName());
			object.insert("enabled",obj->isEnabled());
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

void MainWindow::goButtonClicked()
	{

	QString url;
	int i=-1;
	for (int j=0;j<createdObjects.size();j++)
		if (QString(createdObjects.at(j)->metaObject()->className())=="QFrame")
			i=j;

	if (i>-1)
		{

		int k=-1;
		for (int b=0;b<createdObjects.at(i)->children().size();b++)
			if (createdObjects.at(i)->children().at(b)->objectName().contains("frame_4"))
				k=b;

		if (k>-1)
			{
			if (i>-1)
				{
				int h=-1;
				for (int b=0;b<createdObjects.at(i)->children().at(k)->children().size();b++)
					if (createdObjects.at(i)->children().at(k)->children().at(b)->objectName().contains("lineEdit"))
						h=b;
				if (h>-1)
					{
					QLineEdit* local = reinterpret_cast<QLineEdit *>(createdObjects.at(i)->children().at(k)->children().at(h));
					url= local->text();
					}

				int n=-1;
				for (int b=0;b<createdObjects.at(i)->children().size();b++)
					if (createdObjects.at(i)->children().at(b)->objectName().contains("frame_5"))
						n=b;

				if (n>-1)
					{
					url.remove("http://");
					QWebView* local = reinterpret_cast<QWebView *>(createdObjects.at(i)->children().at(n)->children().at(1));
					local->load(QUrl(QString("http://")+url));
					}
				}
			}
		}

	}
