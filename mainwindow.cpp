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
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
	{
	ui->setupUi(this);
	ui->frame_2->setMinimumWidth(0);
	ui->frame_2->setMaximumWidth(0);

	ui->frame->setMinimumWidth(0);
	ui->frame->setMaximumWidth(0);


	ui->frame_4->setMinimumWidth(0);
	ui->frame_4->setMaximumWidth(0);


	/** !DragDrop! **/
	//Creating dragger
	dragger = new ZDragDrop(this);
	dragger->setObjectList(&createdObjects);

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

	dragger->addWithoutObject(ui->tabButton);
	dragger->addWithoutObject(ui->tabButton_2);
	dragger->addWithoutObject(ui->tabButton_3);

	dragger->addWithoutObject(ui->frame_4);
	dragger->addWithoutObject(ui->pushButton);
	dragger->addWithoutObject(ui->pushButton_2);
	dragger->addWithoutObject(ui->pushButton_3);
	dragger->addWithoutObject(ui->pushButton_4);
	dragger->addWithoutObject(ui->pushButton_5);
	dragger->addWithoutObject(ui->pushButton_6);
	dragger->addWithoutObject(ui->pushButton_7);
	dragger->addWithoutObject(ui->pushButton_8);

	dragger->addWithoutObject(ui->frame);
	dragger->addWithoutObject(ui->toolBox);
	dragger->addWithoutObject(ui->page);
	dragger->addWithoutObject(ui->page_2);

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
	ui->tabButton->setIconSize(QSize(32,32));
	ui->tabButton_2->setIconSize(QSize(32,32));
	ui->tabButton_3->setIconSize(QSize(32,32));

	regulateWidgetGetometryM(ui->frame_3,1.5);
	regulateWidgetGetometryM(ui->label_6,1.5);
	regulateWidgetGetometryM(ui->tabButton);
	regulateWidgetGetometryM(ui->tabButton_2);
	regulateWidgetGetometryM(ui->tabButton_3);
	regulateWidgetGetometryM(ui->backButton);
	regulateWidgetGetometryM(ui->saveButton);
	regulateWidgetGetometryM(ui->forwardButton);
	regulateWidgetGetometryM(ui->loadMasterButton);
	regulateWidgetGetometryM(ui->deleteTempButton);

	regulateWidgetGetometryM(ui->pushButton);
	regulateWidgetGetometryM(ui->pushButton_2);
	regulateWidgetGetometryM(ui->pushButton_3);
	regulateWidgetGetometryM(ui->pushButton_4);
	regulateWidgetGetometryM(ui->pushButton_5);
	regulateWidgetGetometryM(ui->pushButton_6);
	regulateWidgetGetometryM(ui->pushButton_7);
	regulateWidgetGetometryM(ui->pushButton_8);
	regulateWidgetGetometryM(ui->frame_4);
	regulateWidgetGetometryM(ui->frame);
	regulateWidgetGetometryM(ui->toolBox);
	regulateWidgetGetometryM(ui->page);
	regulateWidgetGetometryM(ui->page_2);
	regulateWidgetGetometryM(ui->frame_2);
	regulateWidgetGetometryM(ui->masterRecordList);

#else
	regulateWidgetGetometry(ui->frame_3);
	regulateWidgetGetometry(ui->label_6);
	regulateWidgetGetometry(ui->tabButton);
	regulateWidgetGetometry(ui->tabButton_2);
	regulateWidgetGetometry(ui->tabButton_3);
	regulateWidgetGetometry(ui->backButton);
	regulateWidgetGetometry(ui->saveButton);
	regulateWidgetGetometry(ui->forwardButton);
	regulateWidgetGetometry(ui->loadMasterButton);
	regulateWidgetGetometry(ui->deleteTempButton);
	regulateWidgetGetometry(ui->pushButton);
	regulateWidgetGetometry(ui->pushButton_2);
	regulateWidgetGetometry(ui->pushButton_3);
	regulateWidgetGetometry(ui->pushButton_4);
	regulateWidgetGetometry(ui->pushButton_5);
	regulateWidgetGetometry(ui->pushButton_6);
	regulateWidgetGetometry(ui->pushButton_7);
	regulateWidgetGetometry(ui->pushButton_8);
	regulateWidgetGetometry(ui->frame_4);
	regulateWidgetGetometry(ui->frame);
	regulateWidgetGetometry(ui->toolBox);
	regulateWidgetGetometry(ui->page);
	regulateWidgetGetometry(ui->page_2);
	regulateWidgetGetometry(ui->frame_2);
	regulateWidgetGetometry(ui->masterRecordList);

#endif

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
	for (int i=0;i<createdObjects.size();i++){
		createdObjects.at(i)->close();
		}

	createdObjects.clear();

	/// Getting json datas
	QJsonDocument loadDoc(QJsonDocument::fromJson(jsonData));
	QJsonObject allObjects = loadDoc.object();
	QFont fnt("Arial",9);

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


			obj->setFont(fnt);
			obj->setStyleSheet("background-color:transparent;");
			obj->show();

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			regulateWidgetGetometryMnorm(obj,1.5);
#else
			regulateWidgetGetometry(obj);
#endif
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

			obj->setFont(fnt);
			obj->setStyleSheet("border-image:url(:/pics/plain.png);");
			obj->show();
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			regulateWidgetGetometryMnorm(obj,1.5);
#else
			regulateWidgetGetometry(obj);
#endif
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
			obj->setFont(fnt);
			obj->show();

			//obj->setStyleSheet("background-color:transparent;");

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			regulateWidgetGetometryMnorm(obj,1.5);
#else
			regulateWidgetGetometry(obj);
#endif
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
			obj->setFont(fnt);
			/// Adding object to createdObject
			createdObjects.append(obj);
			///  Showing object
			obj->show();


#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			regulateWidgetGetometryMnorm(obj,1.5);
#else
			regulateWidgetGetometry(obj);
#endif
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

			obj->setFont(fnt);
			obj->setStyleSheet("background-color:transparent;");
			obj->show();
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			regulateWidgetGetometryMnorm(obj,1.5);
#else
			regulateWidgetGetometry(obj);
#endif
			}

		else if ( className == "ZWebBrowser")
			{
			ZWebBrowser* obj = new ZWebBrowser(ui->widget);
			obj->setObjectName(object["objectName"].toString());
			obj->setEnabled(object["enabled"].toBool());
			obj->setGeometry(object["geometry"].toObject()["x"].toInt(),
					object["geometry"].toObject()["y"].toInt(),
					object["geometry"].toObject()["width"].toInt(),
					object["geometry"].toObject()["height"].toInt());
			obj->goUrl(object["url"].toString());

			createdObjects.append(obj);
			///  Showing object
			obj->show();

			for (int i=0;i<obj->children().size();i++)
				{
				dragger->removeWithoutObjectOf((QWidget*)obj->children().at(i));
				dragger->addWithoutObject((QWidget*)obj->children().at(i));
				((QWidget*)obj->children().at(i))->setObjectName(QString("__zwebbrowserbtn%1").arg(i));
				((QWidget*)obj->children().at(i))->setFocusPolicy(Qt::NoFocus);
				((QWidget*)obj->children().at(i))->setStyleSheet(QString("#%1 {"
																		 "background-color: qlineargradient("
																		 "spread:pad, x1:0.5, y1:1, "
																		 "x2:0.488636, y2:0, stop:0.238636 "
																		 "rgba(80, 80, 80, 120), stop:1 "
																		 "rgba(189, 189, 189, 5"
																		 "));"
																		 "border: 1px solid rgba(50,50,50,80);"
																		 "border-radius: 5px;"
																		 "color:white;"
																		 " }"
																		 "#%1:pressed {"
																		 "background-color: rgba(30, 30, 30,200);"
																		 "border: 1px solid rgba(0,0,0,80);"
																		 "border-radius: 5px;"
																		 "color:white;"
																		 " }").arg(((QWidget*)obj->children().at(i))->objectName()));
				}

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			regulateWidgetGetometryMnorm(obj,1.5);
			QRect r = this->frameGeometry();
			this->setGeometry(1,1,1,1);
			this->setGeometry(r);
#else
			regulateWidgetGetometry(obj);
#endif
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
		else if ( className == "ZWebBrowser")
			{

			ZWebBrowser* obj = reinterpret_cast<ZWebBrowser*>(createdObjects.at(i));

			QJsonObject geometry;
			geometry.insert("x",obj->x());
			geometry.insert("y",obj->y());
			geometry.insert("width",obj->width());
			geometry.insert("height",obj->height());

			QJsonObject object;
			object.insert("objectClass","ZWebBrowser");
			object.insert("objectName",obj->objectName());
			object.insert("enabled",obj->isEnabled());
			object.insert("geometry",geometry);
			object.insert("url",obj->url());

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
		ui->masterRecordList->addItem(QString("Version-%1").arg(i));
		}
	ui->masterRecordList->setCurrentRow(databaseManager->getCurrentFileIndex());
	}

void MainWindow::setDatabaseFolderName(const QString& name)
	{
	QFile* fil= new QFile;
	fil->setFileName(":/objectVersion0.json");
	if (!fil->open(QIODevice::ReadOnly))
		return;
	QByteArray buff = fil->readAll();
	fil->close();

	fil->setFileName(QDir::currentPath()+"/"+name + "/objectVersion0.json");
	if (!fil->open(QIODevice::WriteOnly))
		return;
	fil->write(buff);
	fil->close();

	databaseManager = new ZDatabaseManager;
	databaseManager->setCheckTimeout(1000);
	databaseManager->setFileName(QDir::currentPath()+"/"+name,"objectVersion");
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

void MainWindow::on_tabButton_clicked()
	{
	if (ui->frame_2->minimumWidth() != 0)
		{
		ui->frame_2->setMinimumWidth(0);
		ui->frame_2->setMaximumWidth(0);
		}
	else
		{
		ui->frame->setMinimumWidth(0);
		ui->frame->setMaximumWidth(0);
		ui->frame_4->setMinimumWidth(0);
		ui->frame_4->setMaximumWidth(0);

		ui->frame_2->setMinimumWidth(150);
		ui->frame_2->setMaximumWidth(150);
		}
	}

void MainWindow::on_tabButton_2_clicked()
	{
	if (ui->frame->minimumWidth() != 0)
		{
		ui->frame->setMinimumWidth(0);
		ui->frame->setMaximumWidth(0);
		}
	else
		{
		ui->frame_2->setMinimumWidth(0);
		ui->frame_2->setMaximumWidth(0);
		ui->frame_4->setMinimumWidth(0);
		ui->frame_4->setMaximumWidth(0);


		ui->frame->setMinimumWidth(120);
		ui->frame->setMaximumWidth(120);
		}
	}

void MainWindow::on_tabButton_3_clicked()
	{
	if (ui->frame_4->minimumWidth() != 0)
		{
		ui->frame_4->setMinimumWidth(0);
		ui->frame_4->setMaximumWidth(0);
		}
	else
		{
		ui->frame->setMinimumWidth(0);
		ui->frame->setMaximumWidth(0);
		ui->frame_2->setMinimumWidth(0);
		ui->frame_2->setMaximumWidth(0);


		ui->frame_4->setMinimumWidth(100);
		ui->frame_4->setMaximumWidth(100);
		}
	}

void MainWindow::on_pushButton_3_clicked()
	{
	ui->centralWidget->setStyleSheet("#centralWidget{"
									 "border-image: url(:/pics/backgrounds/blue_blur.jpg);"
									 "}");
	}

void MainWindow::on_pushButton_2_clicked()
	{
	ui->centralWidget->setStyleSheet("#centralWidget{"
									 "border-image: url(:/pics/backgrounds/blue_clear.jpg);"
									 "}");
	}

void MainWindow::on_pushButton_4_clicked()
	{
	ui->centralWidget->setStyleSheet("#centralWidget{"
									 "border-image: url(:/pics/backgrounds/green_blur.jpg);"
									 "}");
	}

void MainWindow::on_pushButton_clicked()
	{
	ui->centralWidget->setStyleSheet("#centralWidget{"
									 "border-image: url(:/pics/backgrounds/purple_blur.jpg);"
									 "}");
	}

void MainWindow::on_pushButton_6_clicked()
	{
	ui->centralWidget->setStyleSheet("#centralWidget{"
									 "border-image: url(:/pics/backgrounds/red_blur.jpg);"
									 "}");
	}

void MainWindow::on_pushButton_5_clicked()
	{
	ui->centralWidget->setStyleSheet("#centralWidget{"
									 "border-image: url(:/pics/backgrounds/sea_blur.jpg);"
									 "}");
	}

void MainWindow::on_pushButton_7_clicked()
	{
	ui->centralWidget->setStyleSheet("#centralWidget{"
									 "border-image: url(:/pics/backgrounds/solid_gray.jpg);"
									 "}");
	}

void MainWindow::on_pushButton_8_clicked()
	{
	QString fileName = QFileDialog::getOpenFileName(this,
													tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
	if (!fileName.isEmpty())
		{
		ui->centralWidget->setStyleSheet(QString("#centralWidget{"
												 "border-image: url(%1);"
												 "}").arg(fileName));
		}
	}

void MainWindow::regulateWidgetGetometry(QWidget* widget)
	{
#define MYRESW 1366
#define MYRESH 768

	QDesktopWidget dwidget;
	QRect mainScreenSize = dwidget.screenGeometry(dwidget.primaryScreen());

	float ratioConstantH =    ( (mainScreenSize.width()) / ((float)MYRESW) );
	float ratioConstantV = ( (mainScreenSize.height()) / ((float)MYRESH) );

	if (ratioConstantH>ratioConstantV)
		ratioConstantH=ratioConstantV;
	else
		ratioConstantV=ratioConstantH;

	widget->setMinimumHeight(widget->minimumHeight()*ratioConstantH);
	widget->setMaximumHeight(widget->maximumHeight()*ratioConstantH);
	widget->setMinimumWidth(widget->minimumWidth()*ratioConstantH);
	widget->setMaximumWidth(widget->maximumWidth()*ratioConstantH);
	}

void MainWindow::regulateWidgetGetometryM(QWidget* widget, float exSize)
	{
#define MYRESW 1366
#define MYRESH 768

	QDesktopWidget dwidget;
	QRect mainScreenSize = dwidget.screenGeometry(dwidget.primaryScreen());

	float ratioConstantH =    ( (mainScreenSize.width()) / ((float)MYRESW) );
	float ratioConstantV = ( (mainScreenSize.height()) / ((float)MYRESH) );

	if (ratioConstantH>ratioConstantV)
		ratioConstantH=ratioConstantV;
	else
		ratioConstantV=ratioConstantH;

	widget->setMinimumHeight(widget->minimumHeight()*ratioConstantH*exSize);
	widget->setMaximumHeight(widget->maximumHeight()*ratioConstantH*exSize);
	widget->setMinimumWidth(widget->minimumWidth()*ratioConstantH*exSize);
	widget->setMaximumWidth(widget->maximumWidth()*ratioConstantH*exSize);
	}

void MainWindow::regulateWidgetGetometryMnorm(QWidget* widget, float exSize)
	{
#define MYRESW 1366
#define MYRESH 768

	QDesktopWidget dwidget;
	QRect mainScreenSize = dwidget.screenGeometry(dwidget.primaryScreen());

	float ratioConstantH =    ( (mainScreenSize.width()) / ((float)MYRESW) );
	float ratioConstantV = ( (mainScreenSize.height()) / ((float)MYRESH) );

	if (ratioConstantH>ratioConstantV)
		ratioConstantH=ratioConstantV;
	else
		ratioConstantV=ratioConstantH;

	widget->setGeometry(widget->x()*ratioConstantH*exSize , widget->y()*ratioConstantH*exSize,
						widget->width()*ratioConstantH*exSize, widget->height()*ratioConstantH*exSize);
	}
