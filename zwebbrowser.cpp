#include "zwebbrowser.h"

ZWebBrowser::ZWebBrowser(QWidget *parent) : QWidget(parent)
	{
	QFont arial("Arial", 10, QFont::Normal);
	firstStarted = false;

	parent->installEventFilter(this);

	webWidget = new ZWebWidget(this);

	connect(webWidget,SIGNAL(urlChanged(QString)),this,SLOT(urlChanging(QString)));
	connect(webWidget,SIGNAL(loadingChanged(int)),this,SLOT(loadingChanging(int)));

	backButton = new QPushButton(this);
	backButton->setGeometry(backButton->x(),backButton->y(),30,30);
	backButton->setStyleSheet(".QPushButton{"
							  "border-image: url(:/pics/back.png);"
							  "}"
							  ".QPushButton:pressed {"
							  "border-image: url(:/pics/back2.png);"
							  "}");
	connect(backButton,SIGNAL(clicked(bool)),webWidget,SLOT(goBack()));

	forwardButton = new QPushButton(this);
	forwardButton->setGeometry(forwardButton->x(),forwardButton->y(),30,30);
	forwardButton->setStyleSheet(".QPushButton{"
								 "border-image: url(:/pics/forward.png);"
								 "}"
								 ".QPushButton:pressed {"
								 "border-image: url(:/pics/forward2.png);"
								 "}");
	connect(forwardButton,SIGNAL(clicked(bool)),webWidget,SLOT(goForward()));

	goButton = new QPushButton(this);
	goButton->setGeometry(goButton->x(),goButton->y(),30,30);
	goButton->setStyleSheet(".QPushButton{"
							"border-image: url(:/pics/go3.png);"
							"}"
							".QPushButton:pressed {"
							"border-image: url(:/pics/go4.png);"
							"}");
	connect(goButton,SIGNAL(clicked(bool)),this,SLOT(returnPressed()));
	connect(this,SIGNAL(addressPressed(QString)),webWidget,SLOT(goUrl(QString)));

	stopButton = new QPushButton(this);
	stopButton->setGeometry(stopButton->x(),stopButton->y(),30,30);
	stopButton->setStyleSheet(".QPushButton{"
							  "border-image: url(:/pics/exit.png);"
							  "}"
							  ".QPushButton:pressed {"
							  "border-image: url(:/pics/exit2.png);"
							  "}");
	connect(stopButton,SIGNAL(clicked(bool)),webWidget,SLOT(stop()));

	reloadButton = new QPushButton(this);
	reloadButton->setGeometry(reloadButton->x(),reloadButton->y(),30,30);
	reloadButton->setStyleSheet(".QPushButton{"
								"border-image: url(:/pics/reload.png);"
								"}"
								".QPushButton:pressed {"
								"border-image: url(:/pics/reload2.png);"
								"}");
	connect(reloadButton,SIGNAL(clicked(bool)),webWidget,SLOT(reload()));

	addressLine = new QLineEdit(this);
	addressLine->setFont(arial);
	addressLine->setStyleSheet("border-image: url(:/pics/duz.png);color:white;");
	connect(webWidget,SIGNAL(urlChanged(QString)),addressLine,SLOT(setText(QString)));
	connect(addressLine,SIGNAL(returnPressed()),this,SLOT(returnPressed()));
	connect(this,SIGNAL(addressPressed(QString)),webWidget,SLOT(goUrl(QString)));

	loadingBar = new QProgressBar(this);
	loadingBar->setFont(arial);
	connect(webWidget,SIGNAL(loadingChanged(int)),loadingBar,SLOT(setValue(int)));


#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
	ZVisualRegulator::regulateWidget(backButton,ZVisualRegulator::Custom,false,1.5);
#else
	ZVisualRegulator::regulateWidget(backButton,ZVisualRegulator::Pc,false);
#endif


	}

ZWebBrowser::~ZWebBrowser()
	{
	webWidget->close();
	backButton->close();
	forwardButton->close();
	goButton->close();
	stopButton->close();
	reloadButton->close();
	addressLine->close();
	loadingBar->close();
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
	backButton->setGeometry(5,5, backButton->width() , backButton->height() );
	forwardButton->setGeometry(backButton->x()+backButton->width()+5,5,backButton->width(),backButton->height() );
	addressLine->setGeometry(forwardButton->x()+forwardButton->width()+5,5,this->width() -7*5 -5*backButton->width(),backButton->height() );
	goButton->setGeometry(addressLine->x()+addressLine->width()+5,5,backButton->width(),backButton->height() );
	stopButton->setGeometry(goButton->x()+goButton->width()+5,5,goButton->width(),backButton->height() );
	reloadButton->setGeometry(stopButton->x()+stopButton->width()+5,5,stopButton->width(),backButton->height() );
	webWidget->setGeometry(5,backButton->height()+10,this->width()-10,this->height()-2*backButton->height()-30);
	loadingBar->setGeometry(5,webWidget->y()+webWidget->height()+5,this->width()-10,backButton->height()-10);
	}

