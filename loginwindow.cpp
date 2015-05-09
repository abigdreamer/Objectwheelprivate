#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::LoginWindow)
	{
	ui->setupUi(this);
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
