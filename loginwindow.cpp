#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDesktopWidget>

LoginWindow::LoginWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::LoginWindow)
	{
	ui->setupUi(this);
	connect(ui->emailEdit, SIGNAL(returnPressed()),ui->forwardButton,SIGNAL(clicked()));
	connect(ui->passEdit, SIGNAL(returnPressed()),ui->forwardButton,SIGNAL(clicked()));


#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
	regulateWidgetGetometryM(this);
	regulateWidgetGetometryM(ui->emailEdit);
	regulateWidgetGetometryM(ui->forwardButton);
	regulateWidgetGetometryM(ui->passEdit);
	regulateWidgetGetometryM(ui->label);
#else
	regulateWidgetGetometry(this);
	regulateWidgetGetometry(ui->emailEdit);
	regulateWidgetGetometry(ui->forwardButton);
	regulateWidgetGetometry(ui->passEdit);
	regulateWidgetGetometry(ui->label);
#endif

	}

LoginWindow::~LoginWindow()
	{
	delete ui;
	}

void LoginWindow::regulateWidgetGetometry(QWidget* widget)
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

void LoginWindow::regulateWidgetGetometryM(QWidget* widget)
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

	widget->setMinimumHeight(widget->minimumHeight()*ratioConstantH*2);
	widget->setMaximumHeight(widget->maximumHeight()*ratioConstantH*2);
	widget->setMinimumWidth(widget->minimumWidth()*ratioConstantH*2);
	widget->setMaximumWidth(widget->maximumWidth()*ratioConstantH*2);
	}

void LoginWindow::on_forwardButton_clicked()
	{
	if (!ui->emailEdit->text().isEmpty() && !ui->passEdit->text().isEmpty())
		{
		QString generatedHash = QCryptographicHash::hash(QByteArray().append(ui->emailEdit->text()+ui->passEdit->text()),QCryptographicHash::Md5).toHex();
		QDir dir(QDir::currentPath()+"/"+generatedHash);
		if (dir.exists())
			{
			mainScreen = new MainWindow;
			mainScreen->setDatabaseFolderName(generatedHash);
			mainScreen->move( QApplication::desktop()->availableGeometry().center() - mainScreen->rect().center() );
			mainScreen->show();
			this->close();
			}
		else
			{
			err.setText("User not found. Do you want to create a new one?");
			err.setWindowTitle("Info!");
			err.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
			err.setIcon(QMessageBox::Warning);
			int ret=err.exec();
			mainScreen = new MainWindow;
			switch (ret)
				{
				case QMessageBox::Ok :
					dir.mkpath(QDir::currentPath()+"/"+generatedHash);
					mainScreen->setDatabaseFolderName(generatedHash);
					mainScreen->move( QApplication::desktop()->availableGeometry().center() - mainScreen->rect().center() );
					mainScreen->show();
					this->close();
				break;

				case QMessageBox::Cancel :
					this->close();
				break;

				default:
					this->close();
				break;
				}
			}
		}
	else
		{
		err.setText("Password/Email field can not be empty!");
		err.setWindowTitle("Warning!");
		err.setIcon(QMessageBox::Warning);
		err.exec();
		}
	}
