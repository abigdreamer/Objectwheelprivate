/* Pro dosyasına şu kodlar eklenmeli

qtHaveModule(webengine) {
		QT += webengine quickwidgets
		DEFINES += QT_WEBVIEW_WEBENGINE_BACKEND
}else{
QT += quickwidgets
}

*/

#ifndef ZWEBWIDGET_H
#define ZWEBWIDGET_H

#include <QObject>
#include <QQuickWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFile>
#include <QDir>

#ifdef QT_WEBVIEW_WEBENGINE_BACKEND
#include <QtWebEngine>
#endif // QT_WEBVIEW_WEBENGINE_BACKEND

class ZWebWidget : public QQuickWidget
	{
		Q_OBJECT
	private:
		const static char* qmlSource;
		QObject* qmlRootObject;

	public:

		explicit ZWebWidget(QWidget* parent = 0);
		~ZWebWidget();
		int loadingProgress();
		QString url();

	signals:
		void loadingChanged(int);
		void urlChanged(QString);

	public slots:
		void goUrl(const QString& url);
		void goForward();
		void goBack();
		void reload();
		void stop();

	private slots:
		void loadingChanging(int p )
			{emit loadingChanged(p);}

		void urlChanging(QString s)
			{emit urlChanged(s);}

	};

#endif // ZWEBWIDGET_H
