#ifndef ZWEBBROWSER_H
#define ZWEBBROWSER_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QEvent>
#include <QTimer>
#include "zwebwidget.h"
#include "zlayout.h"

class ZWebBrowser : public QWidget
	{
		Q_OBJECT
	public:
		explicit ZWebBrowser(QWidget *parent = 0);
		ZWebWidget* webWidget;
		ZLayout* lay;

		QTimer* resizer;

		QPushButton* backButton;
		QPushButton* forwardButton;
		QPushButton* goButton;
		QPushButton* stopButton;
		QPushButton* reloadButton;
		QLineEdit* addressLine;
		QProgressBar* loadingBar;

		bool firstStarted;
		void paintEvent(QPaintEvent *);
		void resizeEvent(QResizeEvent *);

		int loadingProgress()
			{return webWidget->loadingProgress();}
		QString url()
			{return webWidget->url();}
	signals:
		void loadingChanged(int);
		void urlChanged(QString);

		void addressPressed(QString s);

	public slots:
		void returnPressed()
			{emit addressPressed(addressLine->text());}

		void goUrl(const QString& url)
			{webWidget->goUrl(url);}
		void goForward()
			{webWidget->goForward();}
		void goBack()
			{webWidget->goBack();}
		void reload()
			{webWidget->reload();}
		void stop()
			{webWidget->stop();}

	private slots:
		void loadingChanging(int p )
			{emit loadingChanged(p);}

		void urlChanging(QString s)
			{emit urlChanged(s);}

	};

#endif // ZWEBBROWSER_H
