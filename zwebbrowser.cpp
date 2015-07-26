#include "zwebbrowser.h"

ZWebBrowser::ZWebBrowser(QWidget *parent) : QWidget(parent)
	{
	QFont arial("Arial", 6, QFont::Normal);
	firstStarted = false;

	parent->installEventFilter(this);

	webWidget = new ZWebWidget(this);

	connect(webWidget,SIGNAL(urlChanged(QString)),this,SLOT(urlChanging(QString)));
	connect(webWidget,SIGNAL(loadingChanged(int)),this,SLOT(loadingChanging(int)));

	backButton = new QPushButton(this);
	backButton->setText("Back");
	backButton->setFont(arial);
	connect(backButton,SIGNAL(clicked(bool)),webWidget,SLOT(goBack()));

	forwardButton = new QPushButton(this);
	forwardButton->setText("Forward");
	forwardButton->setFont(arial);
	connect(forwardButton,SIGNAL(clicked(bool)),webWidget,SLOT(goForward()));

	goButton = new QPushButton(this);
	goButton->setText("Go");
	goButton->setFont(arial);
	connect(goButton,SIGNAL(clicked(bool)),this,SLOT(returnPressed()));
	connect(this,SIGNAL(addressPressed(QString)),webWidget,SLOT(goUrl(QString)));

	stopButton = new QPushButton(this);
	stopButton->setText("Stop");
	stopButton->setFont(arial);
	connect(stopButton,SIGNAL(clicked(bool)),webWidget,SLOT(stop()));

	reloadButton = new QPushButton(this);
	reloadButton->setText("Reload");
	reloadButton->setFont(arial);
	connect(reloadButton,SIGNAL(clicked(bool)),webWidget,SLOT(reload()));

	addressLine = new QLineEdit(this);
	addressLine->setFont(arial);
	connect(webWidget,SIGNAL(urlChanged(QString)),addressLine,SLOT(setText(QString)));
	connect(addressLine,SIGNAL(returnPressed()),this,SLOT(returnPressed()));
	connect(this,SIGNAL(addressPressed(QString)),webWidget,SLOT(goUrl(QString)));

	loadingBar = new QProgressBar(this);
	loadingBar->setFont(arial);
	connect(webWidget,SIGNAL(loadingChanged(int)),loadingBar,SLOT(setValue(int)));

	}

void ZWebBrowser::paintEvent(QPaintEvent*)
	{
	QStyleOption o;
	o.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
	}

void ZWebBrowser::resizeEvent(QResizeEvent*)
	{
	if (firstStarted==false)
		{
		firstStarted=true;
		setStyleSheet(QString("#%1 {border: 1px solid rgba(0,0,0,190);"
							  "border-radius: 5px;"
							  "background-color: rgba(0, 0, 0, 90);}").arg(objectName()));
		}
	backButton->setGeometry(5,5, (this->width()-70)/7 , 20 );
	forwardButton->setGeometry(backButton->x()+backButton->width()+5,5,backButton->width(),20 );
	addressLine->setGeometry(forwardButton->x()+forwardButton->width()+5,5,forwardButton->width()*2 + 35,20 );
	goButton->setGeometry(addressLine->x()+addressLine->width()+5,5,backButton->width(),20 );
	stopButton->setGeometry(goButton->x()+goButton->width()+5,5,goButton->width(),20 );
	reloadButton->setGeometry(stopButton->x()+stopButton->width()+5,5,stopButton->width(),20 );
	webWidget->setGeometry(5,30,this->width()-10,this->height()-75);
	loadingBar->setGeometry(5,webWidget->y()+webWidget->height()+5,this->width()-10,20);
	}

