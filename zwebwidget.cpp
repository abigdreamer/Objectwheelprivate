#include "zwebwidget.h"
const char* ZWebWidget::qmlSource = "import QtQuick 2.2 \n"
									"import QtWebView 1.0 \n"
									"WebView { \n"
									"    id: webView \n"
									"    objectName: \"webView\" \n"
									"    url: \"https://m.facebook.com\" \n"
									"    signal loadingProgressChanged(int p) \n"
									"    signal urlChanged(string s); \n"
									"    onLoadProgressChanged:loadingProgressChanged(loadProgress), urlChanged(url) \n"
									"}";

ZWebWidget::ZWebWidget(QWidget* parent) : QQuickWidget(parent)
	{
#ifdef QT_WEBVIEW_WEBENGINE_BACKEND
	QtWebEngine::initialize();
#endif // QT_WEBVIEW_WEBENGINE_BACKEND

	QFile* wr = new QFile(QDir::currentPath() + "/source.qml");
	if (! wr->open(QIODevice::WriteOnly)) {
		qWarning("ZWebWidget : File can't open.");
		return;
		}
	wr->write(qmlSource);
	wr->close();
	delete wr;

	setGeometry(QRect(70, 70, 300, 200));
	setResizeMode(QQuickWidget::SizeRootObjectToView);
	setSource(QUrl("qrc:/source.qml"));

	qmlRootObject = reinterpret_cast<QObject*>(rootObject());

	QObject::connect(qmlRootObject, SIGNAL(loadingProgressChanged(int)),
					 this, SLOT(loadingChanging(int)));
	QObject::connect(qmlRootObject, SIGNAL(urlChanged(QString)),
					 this, SLOT(urlChanging(QString)));
	}


ZWebWidget::~ZWebWidget()
	{
	qmlRootObject->deleteLater();
	delete qmlRootObject;
	}

int ZWebWidget::loadingProgress()
	{
	if (qmlRootObject)
		return qmlRootObject->property("loadProgress").toInt();
	else
		{
		qWarning("ZWebWidget : Url couldn't load.");
		return 0;
		}
	}

QString ZWebWidget::url()
	{
	if (qmlRootObject)
		return qmlRootObject->property("url").toString();
	else
		{
		qWarning("ZWebWidget : Url couldn't go back.");
		return 0;
		}
	}

void ZWebWidget::goUrl(const QString& url)
	{
	QString localUrl=url;
	localUrl.remove("http://");
	localUrl.push_front("http://");
	if (qmlRootObject)
		qmlRootObject->setProperty("url", localUrl);
	else
		qWarning("ZWebWidget : Url couldn't load.");
	}

void ZWebWidget::goForward()
	{
	if (qmlRootObject)
		QMetaObject::invokeMethod(qmlRootObject, "goForward");
	else
		qWarning("ZWebWidget : Url couldn't go forward.");
	}

void ZWebWidget::goBack()
	{
	if (qmlRootObject)
		QMetaObject::invokeMethod(qmlRootObject, "goBack");
	else
		qWarning("ZWebWidget : Url couldn't go back.");
	}

void ZWebWidget::reload()
	{
	if (qmlRootObject)
		QMetaObject::invokeMethod(qmlRootObject, "reload");
	else
		qWarning("ZWebWidget : Url couldn't reload.");
	}

void ZWebWidget::stop()
	{
	if (qmlRootObject)
		QMetaObject::invokeMethod(qmlRootObject, "stop");
	else
		qWarning("ZWebWidget : Url couldn't stop.");
	}
