#include "mainwindow.h"
#include "ui_mainwindow.h"
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

	connect(ui->autoFit,SIGNAL(valueChanged(int)),this,SLOT(scaleDesignArea(int)));
	/** !DragDrop! **/
	//Creating dragger
	dragger = new ZDragDrop(this);
	dragger->setObjectList(&createdObjects,&firstRects);

	//For eventFilter
	qApp->installEventFilter(this);

	foreach( QWidget* w, ui->toolBox->findChildren<QWidget*>() )
		{
		if( w->inherits("QToolBoxButton") )
			{
			QAbstractButton* button = qobject_cast<QAbstractButton*>(w);
			button->setFocusPolicy(Qt::NoFocus);
			button->setStyleSheet("background:transparent;");
			dragger->addWithoutObject(button);
			}
		}

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
	dragger->addWithoutObject(ui->autoFit);
	dragger->addWithoutObject(ui->frame);
	dragger->addWithoutObject(ui->toolBox);
	dragger->addWithoutObject(ui->page);
	dragger->addWithoutObject(ui->page_2);
	dragger->addToolBoxObject(ui->pushButton_9);
	dragger->addToolBoxObject(ui->label);
	dragger->addToolBoxObject(ui->checkBox);
	dragger->addToolBoxObject(ui->lineEdit);
	dragger->addToolBoxObject(ui->label_2);
	dragger->addToolBoxObject(ui->label_3);

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
	ui->tabButton->setIconSize(QSize(32,32));
	ui->tabButton_2->setIconSize(QSize(32,32));
	ui->tabButton_3->setIconSize(QSize(32,32));
	ui->autoFit->setGeometry(ui->autoFit->x(),ui->autoFit->y(),ui->autoFit->width()+20,ui->autoFit->height()+20);

	ZVisualRegulator::regulateWidget(ui->frame_3, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->label_6, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->tabButton, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->tabButton_2, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->tabButton_3, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->backButton, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->saveButton, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->forwardButton, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->loadMasterButton, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->deleteTempButton, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->pushButton, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->pushButton_2, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->pushButton_3, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->pushButton_4, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->pushButton_5, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->pushButton_6, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->pushButton_7, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->pushButton_8, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->frame_4, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->frame, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->frame_2, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->lineEdit, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->pushButton_9, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->label_2, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->label_3, ZVisualRegulator::Mobile);

	ZVisualRegulator::regulateFont(ui->pushButton, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->pushButton_2, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->pushButton_3, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->pushButton_4, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->pushButton_5, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->pushButton_6, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->pushButton_7, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->pushButton_8, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->lineEdit, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->pushButton_9, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->checkBox, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->label, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->toolBox, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->masterRecordList, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->label_2, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateFont(ui->label_3, ZVisualRegulator::Mobile);

#else	
	ZVisualRegulator::regulateWidget(ui->frame_3, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->label_6, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->tabButton, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->tabButton_2, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->tabButton_3, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->backButton, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->saveButton, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->forwardButton, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->loadMasterButton, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->deleteTempButton, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->pushButton, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->pushButton_2, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->pushButton_3, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->pushButton_4, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->pushButton_5, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->pushButton_6, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->pushButton_7, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->pushButton_8, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->frame_4, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->frame, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->frame_2, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->lineEdit, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->pushButton_9, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->label_2, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->label_3, ZVisualRegulator::Pc);

	ZVisualRegulator::regulateFont(ui->pushButton, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->pushButton_2, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->pushButton_3, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->pushButton_4, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->pushButton_5, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->pushButton_6, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->pushButton_7, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->pushButton_8, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->lineEdit, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->pushButton_9, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->checkBox, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->label, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->toolBox, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->masterRecordList, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->label_2, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateFont(ui->label_3, ZVisualRegulator::Pc);
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

void MainWindow::resizeEvent(QResizeEvent*)
	{
	ui->autoFit->move(5,ui->widget->height()-5-ui->autoFit->height());
	}

void MainWindow::createObjects(const QByteArray& jsonData)
	{
	for (int i=0;i<createdObjects.size();i++){
		createdObjects.at(i)->close();
		}

	createdObjects.clear();
	firstRects.clear();

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
			obj->setStyleSheet(object["styleSheet"].toString());
			obj->setFocusPolicy(Qt::NoFocus);

			createdObjects.append(obj);
			///  Showing object


			obj->setFont(fnt);
			obj->show();

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Custom,false,1.5);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Custom,1.5);
#else
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Pc,false);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Pc);
#endif
			firstRects.append(obj->geometry());

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
			obj->setStyleSheet(object["styleSheet"].toString());

			/// Adding object to createdObject
			createdObjects.append(obj);

			///  Showing object

			obj->setFont(fnt);
			obj->show();
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Custom,false,1.5);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Custom,1.5);
#else
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Pc,false);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Pc);
#endif
			firstRects.append(obj->geometry());

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
			obj->setStyleSheet(object["styleSheet"].toString());
			obj->setFocusPolicy(Qt::NoFocus);
			/// Adding object to createdObject
			createdObjects.append(obj);

			///  Showing object
			obj->setFont(fnt);
			obj->show();

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Custom,false,1.5);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Custom,1.5);
#else
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Pc,false);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Pc);
#endif

			firstRects.append(obj->geometry());

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
			obj->setFocusPolicy(Qt::NoFocus);
			/// Adding object to createdObject
			createdObjects.append(obj);

			///  Showing object
			obj->show();


#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Custom,false,1.5);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Custom,1.5);
#else
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Pc,false);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Pc);
#endif
			firstRects.append(obj->geometry());

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
			obj->setStyleSheet(object["styleSheet"].toString());
			obj->setFocusPolicy(Qt::NoFocus);
			/// Adding object to createdObject
			createdObjects.append(obj);

			///  Showing object

			obj->setFont(fnt);
			obj->show();
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Custom,false,1.5);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Custom,1.5);
#else
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Pc,false);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Pc);
#endif
			firstRects.append(obj->geometry());

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
			obj->setStyleSheet(object["styleSheet"].toString());

			createdObjects.append(obj);

			///  Showing object
			obj->show();

			for (int i=0;i<obj->children().size();i++)
				{
				dragger->removeWithoutObjectOf((QWidget*)obj->children().at(i));
				dragger->addWithoutObject((QWidget*)obj->children().at(i));
				((QWidget*)obj->children().at(i))->setObjectName(QString("__zwebbrowserbtn%1").arg(i));
				((QWidget*)obj->children().at(i))->setFocusPolicy(Qt::NoFocus);

				if (QString(((QWidget*)obj->children().at(i))->metaObject()->className())=="QProgressBar")
					((QWidget*)obj->children().at(i))->setStyleSheet("QProgressBar {"
																	 "text-align: center;"
																	 "border : 1px solid rgb(90, 90, 100);"
																	 "background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,"
																	 "stop: 0 #fff,"
																	 "stop: 0.4999 #eee,"
																	 "stop: 0.5 #ddd,"
																	 "stop: 1 #eee);"
																	 "}QProgressBar::chunk {"
																	 "background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,"
																	 "stop: 0 #78d,"
																	 "stop: 0.4999 #46a,"
																	 "stop: 0.5 #45a,"
																	 "stop: 1 #238 );}");
				else if (QString(((QWidget*)obj->children().at(i))->metaObject()->className())=="QLineEdit")
					((QWidget*)obj->children().at(i))->setFocusPolicy(Qt::StrongFocus);
				}

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Custom,false,1.5);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Custom,1.5);
			QRect r = this->frameGeometry();
			this->setGeometry(1,1,1,1);
			this->setGeometry(r);
#else
			ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Pc,false);
			ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Pc);
#endif
			firstRects.append(obj->geometry());

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
			object.insert("styleSheet",obj->styleSheet());
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
			object.insert("styleSheet",obj->styleSheet());

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
			object.insert("styleSheet",obj->styleSheet());

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
			object.insert("styleSheet",obj->styleSheet());

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
			object.insert("styleSheet",obj->styleSheet());

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
			object.insert("styleSheet",obj->styleSheet());

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
		update();
		}
	else
		{
		ui->frame->setMinimumWidth(0);
		ui->frame->setMaximumWidth(0);
		ui->frame_4->setMinimumWidth(0);
		ui->frame_4->setMaximumWidth(0);
		ui->frame_2->setMinimumWidth(150);
		ui->frame_2->setMaximumWidth(150);
		update();
		}
	}

void MainWindow::on_tabButton_2_clicked()
	{
	if (ui->frame->minimumWidth() != 0)
		{
		ui->frame->setMinimumWidth(0);
		ui->frame->setMaximumWidth(0);
		update();
		}
	else
		{
		ui->frame_2->setMinimumWidth(0);
		ui->frame_2->setMaximumWidth(0);
		ui->frame_4->setMinimumWidth(0);
		ui->frame_4->setMaximumWidth(0);
		ui->frame->setMinimumWidth(120);
		ui->frame->setMaximumWidth(120);
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
		ZVisualRegulator::regulateWidget(ui->frame, ZVisualRegulator::Mobile);
#else
		ZVisualRegulator::regulateWidget(ui->frame, ZVisualRegulator::Pc);
#endif
		update();
		}
	}

void MainWindow::on_tabButton_3_clicked()
	{
	if (ui->frame_4->minimumWidth() != 0)
		{
		ui->frame_4->setMinimumWidth(0);
		ui->frame_4->setMaximumWidth(0);
		update();
		}
	else
		{
		ui->frame->setMinimumWidth(0);
		ui->frame->setMaximumWidth(0);
		ui->frame_2->setMinimumWidth(0);
		ui->frame_2->setMaximumWidth(0);
		ui->frame_4->setMinimumWidth(100);
		ui->frame_4->setMaximumWidth(100);
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
		ZVisualRegulator::regulateWidget(ui->frame_4, ZVisualRegulator::Mobile);
#else
		ZVisualRegulator::regulateWidget(ui->frame_4, ZVisualRegulator::Pc);
#endif
		update();
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

void MainWindow::scaleDesignArea(int val)
	{
	float value = val / 100.0;

	if (value > 0)
		{
		for (int i=0;i<createdObjects.size();i++)
			{
			QWidget* obj = (QWidget*) createdObjects.at(i);
			obj->setGeometry(firstRects.at(i).x() * value ,
							 firstRects.at(i).y() * value ,
							 firstRects.at(i).width() * value ,
							 firstRects.at(i).height() * value);
			}
		}
	update();
	}
