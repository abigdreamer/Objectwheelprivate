#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug> // For testing

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
	QFile yy;
	yy.setFileName("new2.txt");
	yy.open(QIODevice::ReadWrite);
	yy.write(databaseManager->getFile());
	yy.close();
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

