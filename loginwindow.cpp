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
	QFont ft("Arial", 14, QFont::Normal);
	QFont ft2("Arial", 18, QFont::Normal);
	ZVisualRegulator::regulateWidget(ui->emailEdit, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->forwardButton, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->passEdit, ZVisualRegulator::Mobile);
	ZVisualRegulator::regulateWidget(ui->label, ZVisualRegulator::Mobile);

	ui->emailEdit->setFont(ft);
	ui->emailLabel->setFont(ft);
	ui->passEdit->setFont(ft);
	ui->passLabel->setFont(ft);
	ui->signinLabel->setFont(ft2);
#else
	ZVisualRegulator::regulateWidget(ui->emailEdit, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->forwardButton, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->passEdit, ZVisualRegulator::Pc);
	ZVisualRegulator::regulateWidget(ui->label, ZVisualRegulator::Pc);
#endif

	}

LoginWindow::~LoginWindow()
	{
	delete ui;
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
