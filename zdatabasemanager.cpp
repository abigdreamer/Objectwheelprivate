#include "zdatabasemanager.h"

void ZDatabaseManager::databaseChangeEvent(const DatabaseChangeEvents event)
	{

	switch (event) {
		case CurrentFileDoesntExist:
			if ( !QFile::exists( databaseDirectory + "/" + fileNameBody + "0.json" ) )
				{
				/* Hem currentFile işareçi dosyası hem sıfır numaralı record yoksa; Bir adet boş { }
				 * sıfır numaralı recordu ekle ve ardından bir currentFile oluşturup bu dosyanın bilgilerini
				 * ona ekle ve ardından currentFileIndex ini ayarla ve ardından varolan fileHashMap ı temizle
				 * ve bu yeni oluşturduğumuz recordun bilgilerini içine ekle */
				fileManager->setFileName( databaseDirectory + "/" + fileNameBody + "0.json" );
				if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
					{
					cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
					break;
					}
				fileManager->write( QByteArray().append("{ }") );
				QString hashBuff = QCryptographicHash::hash(fileManager->readAll(), QCryptographicHash::Md5).toHex();
				fileManager->close();

				fileManager->setFileName( databaseDirectory + "/" + QString(CURRENTFILE));
				if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
					{
					cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
					break;
					}
				fileManager->write( QByteArray().append("0\n") );
				fileManager->write( QByteArray().append(hashBuff) );
				fileManager->close();

				currentFileIndex=0;
				fileHashMap.clear();
				fileHashMap.insert(0,hashBuff);
				}
			else
				{
				/* CurrentFile yok ancak en az bir record varsa; Sıfır nolu recorddan yukarı doğru tara
				 * ve en son geçerli (dosya var) recordu ve toplam record sayısını öğren ve ardından
				 * fileHashMap ı temizleyip record bilgilerini fileHashMap a ekle ve ardından currentFileIndex i de
				 * set et ve ardından yeni bir currentFile oluşturup son numaralı elemanın bilgilerini onun içine koy */
				int lastIndex=1;
				for ( ;QFile::exists( databaseDirectory + "/" + fileNameBody + QString("%1.json").arg(lastIndex) ); lastIndex++ );
				lastIndex-=1;
				currentFileIndex=lastIndex;
				fileHashMap.clear();

				for (int i=0; i<=lastIndex;i++)
					{
					fileManager->setFileName( databaseDirectory + "/" + fileNameBody + QString("%1.json").arg(i) );
					if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
						{
						cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
						break;
						}
					fileHashMap.insert( i, QCryptographicHash::hash(fileManager->readAll(), QCryptographicHash::Md5).toHex() );
					fileManager->close();
					}

				fileManager->setFileName( databaseDirectory + "/" + QString(CURRENTFILE) );
				if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
					{
					cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
					break;
					}
				fileManager->write( QByteArray().append( QString("%1\n").arg(lastIndex) ) );
				fileManager->write( QByteArray().append( fileHashMap.value(lastIndex) ) );
				fileManager->close();
				}


			break;
		case CurrentFileCantOpen:
			cerr << (QString("%1:%2 File can't delete!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
			break;
		case CurrentFileHashIsNull:
			if ( QFile::exists( databaseDirectory + "/" + QString(CURRENTFILE) ) )
				if ( !QFile::remove( databaseDirectory + "/" + QString(CURRENTFILE) ) )
					cerr << (QString("%1:%2 File can't delete!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
			break;
		case CurrentFileIndexIsNull:
			if ( QFile::exists( databaseDirectory + "/" + QString(CURRENTFILE) ) )
				if ( !QFile::remove( databaseDirectory + "/" + QString(CURRENTFILE) ) )
					cerr << (QString("%1:%2 File can't delete!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
			break;
		case CurrenFileIndexChanged:
			fileManager->setFileName( databaseDirectory + "/" + QString(CURRENTFILE) );
			if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
				{
				cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
				break;
				}
			currentFileIndex = QString(fileManager->readLine().at(0)).toInt();
			fileManager->close();
			break;
		case CurrentFileHashChanged:
			fileManager->setFileName( databaseDirectory + "/" + QString(CURRENTFILE) );
			if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
				{
				cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
				break;
				}
			fileManager->readLine();
			fileHashMap[currentFileIndex] = fileManager->readLine();
			fileManager->close();
			break;
		case CurrentRecordDoesntExist:
			if ( QFile::exists( databaseDirectory + "/" + QString(CURRENTFILE) ) )
				if ( !QFile::remove( databaseDirectory + "/" + QString(CURRENTFILE) ) )
					cerr << (QString("%1:%2 File can't delete!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
			break;
		case CurrentRecordCantOpen:
			cerr << ("databaseChangeEvent() : File can't open!");
			break;
		case CurrenRecordHashChanged:
			fileManager->setFileName( databaseDirectory + "/" + fileNameBody + QString::number(currentFileIndex) + ".json" );
			if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
				{
				cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
				break;
				}
			fileHashMap[currentFileIndex]=QCryptographicHash::hash(fileManager->readAll(), QCryptographicHash::Md5).toHex();
			fileManager->close();

			if ( QFile::exists( databaseDirectory + "/" + QString(CURRENTFILE) ) )
				if ( !QFile::remove( databaseDirectory + "/" + QString(CURRENTFILE) ) )
					{
					cerr << (QString("%1:%2 File can't delete!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
					break;
					}

			fileManager->setFileName( databaseDirectory + "/" + QString(CURRENTFILE) );
			if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
				{
				cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
				break;
				}
			fileManager->write( QByteArray().append( QString("%1\n").arg(currentFileIndex) ) );
			fileManager->write( QByteArray().append( fileHashMap.value(currentFileIndex) ) );
			fileManager->close();
			break;
		}

	emit databaseChanged();
	}

ZDatabaseManager::ZDatabaseManager(QObject *parent) : QObject(parent)
	{ checkTimeout=1000; changeListenerTimer=new QTimer; fileManager=new QFile;}

ZDatabaseManager::ZDatabaseManager(const QString& databasedirectory, const QString& filenamebody, const int msecond)
	{
	databaseDirectory=databasedirectory;
	fileNameBody=filenamebody;
	checkTimeout=msecond;
	changeListenerTimer=new QTimer;
	fileManager=new QFile;
	}

void ZDatabaseManager::setFileName(const QString& databasedirectory, const QString& filenamebody)
	{ databaseDirectory=databasedirectory; fileNameBody=filenamebody;}

void ZDatabaseManager::setCheckTimeout(const int msecond)
	{ checkTimeout=msecond; }

void ZDatabaseManager::setCurrentFileIndex(const int index)
	{
	currentFileIndex=index;
	if ( QFile::exists( databaseDirectory + "/" + QString(CURRENTFILE) ) )
		if ( !QFile::remove( databaseDirectory + "/" + QString(CURRENTFILE) ) )
			{
			cerr << (QString("%1:%2 File can't delete!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
			return;
			}

	fileManager->setFileName( databaseDirectory + "/" + QString(CURRENTFILE) );
	if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
		{
		cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
		return;
		}
	fileManager->write( QByteArray().append( QString("%1\n").arg(index) ) );
	fileManager->write( QByteArray().append(  "null" ) );
	fileManager->close();
	}

bool ZDatabaseManager::addFile(const QByteArray& file)
	{
	for (int i=currentFileIndex+1;i<fileHashMap.size();i++)
		{
		fileHashMap.remove(i);
		if ( QFile::exists( databaseDirectory + "/" + fileNameBody + QString::number(i) + ".json" ) )
			if ( !QFile::remove( databaseDirectory + "/" + fileNameBody + QString::number(i) + ".json" ) )
				{ cerr << (QString("%1:%2 File can't delete!").arg(__FILE__).arg(__LINE__).toStdString().c_str()); return false; }
		}
	currentFileIndex+=1;

	fileHashMap.insert( currentFileIndex, QCryptographicHash::hash(file, QCryptographicHash::Md5).toHex() );
	fileManager->setFileName( databaseDirectory + "/" + fileNameBody + QString::number(currentFileIndex) + ".json" );
	if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
		{ cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str()); return false; }
	fileManager->write(file);
	fileManager->close();

	if ( QFile::exists( databaseDirectory + "/" + QString(CURRENTFILE) ) )
		if ( !QFile::remove( databaseDirectory + "/" + QString(CURRENTFILE) ) )
			{ cerr << (QString("%1:%2 File can't delete!").arg(__FILE__).arg(__LINE__).toStdString().c_str()); return false; }

	fileManager->setFileName( databaseDirectory + "/" + QString(CURRENTFILE) );
	if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
		{ cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str()); return false; }
	fileManager->write( QByteArray().append( QString("%1\n").arg(currentFileIndex) ) );
	fileManager->write( QCryptographicHash::hash(file, QCryptographicHash::Md5).toHex() );
	fileManager->close();
	return true;
	}

bool ZDatabaseManager::removeFile()
	{
	for (int i=currentFileIndex;i<fileHashMap.size();i++)
		{
		fileHashMap.remove(i);
		if ( QFile::exists( databaseDirectory + "/" + fileNameBody + QString::number(i) + ".json" ) )
			if ( !QFile::remove( databaseDirectory + "/" + fileNameBody + QString::number(i) + ".json" ) )
				{ cerr << (QString("%1:%2 File can't delete!").arg(__FILE__).arg(__LINE__).toStdString().c_str()); return false; }
		}
	currentFileIndex-=1;

	if ( QFile::exists( databaseDirectory + "/" + QString(CURRENTFILE) ) )
		if ( !QFile::remove( databaseDirectory + "/" + QString(CURRENTFILE) ) )
			{ cerr << (QString("%1:%2 File can't delete!").arg(__FILE__).arg(__LINE__).toStdString().c_str()); return false; }

	fileManager->setFileName( databaseDirectory + "/" + QString(CURRENTFILE) );
	if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
		{ cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str()); return false; }
	fileManager->write( QByteArray().append( QString("%1\n").arg(currentFileIndex) ) );
	fileManager->write( QByteArray().append( fileHashMap.value(currentFileIndex) ) );
	fileManager->close();
	return true;
	}

void ZDatabaseManager::startChangeListener()
	{
	if ( !databaseDirectory.isNull() && !fileNameBody.isNull() && checkTimeout>0)
		{
		connect(changeListenerTimer,SIGNAL(timeout()),this,SLOT(changeListener()));
		changeListenerTimer->start(checkTimeout);
		}
	else
		cerr << (QString("%1:%2 Timer doesn't start!").arg(__FILE__).arg(__LINE__).toStdString().c_str());
	}

const QString&ZDatabaseManager::getFileName() const
	{ return fileNameBody; }

const int&ZDatabaseManager::getCheckTimeout() const
	{ return checkTimeout; }

const int&ZDatabaseManager::getCurrentFileIndex() const
	{ return currentFileIndex; }

QByteArray ZDatabaseManager::getFile() const
	{
	fileManager->setFileName( databaseDirectory + "/" + fileNameBody + QString::number(currentFileIndex) + ".json" );
	if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
		{ cerr << (QString("%1:%2 File can't open!").arg(__FILE__).arg(__LINE__).toStdString().c_str()); return 0; }
	QByteArray dataBuff = fileManager->readAll();
	fileManager->close();
	return dataBuff;
	}

bool ZDatabaseManager::isChangeListenerActive() const
	{
	return changeListenerTimer->isActive();
	}

ZDatabaseManager::~ZDatabaseManager()
	{ }

void ZDatabaseManager::changeListener()
	{
	if ( !QFile::exists( databaseDirectory + "/" + QString(CURRENTFILE) ) )
		{
		databaseChangeEvent(CurrentFileDoesntExist);
		return;
		}
	else
		{
		fileManager->setFileName( databaseDirectory + "/" + QString(CURRENTFILE) );
		if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
			{
			if (fileManager->isOpen())
				fileManager->close();
			databaseChangeEvent(CurrentFileCantOpen);
			return;
			}
		else
			{
			int indexBuff = QString(fileManager->readLine().at(0)).toInt();
			QString hashBuff = fileManager->readLine();
			if ( hashBuff.isNull() )
				{
				if (fileManager->isOpen())
					fileManager->close();
				databaseChangeEvent(CurrentFileHashIsNull);
				return;
				}
			else if ( indexBuff < 0 )
				{
				if (fileManager->isOpen())
					fileManager->close();
				databaseChangeEvent(CurrentFileIndexIsNull);
				return;
				}
			else if ( currentFileIndex != indexBuff )
				{
				if (fileManager->isOpen())
					fileManager->close();
				databaseChangeEvent(CurrenFileIndexChanged);
				return;
				}
			else if ( fileHashMap.value(indexBuff) != hashBuff )
				{
				if (fileManager->isOpen())
					fileManager->close();
				databaseChangeEvent(CurrentFileHashChanged);
				return;
				}
			else if ( !QFile::exists( databaseDirectory + "/" + fileNameBody + QString::number(indexBuff) + ".json" ) )
				{
				if (fileManager->isOpen())
					fileManager->close();
				databaseChangeEvent(CurrentRecordDoesntExist);
				return;
				}
			else
				{
				if (fileManager->isOpen())
					fileManager->close();
				fileManager->setFileName( databaseDirectory + "/" + fileNameBody + QString::number(indexBuff) + ".json" );
				if ( !fileManager->open(QIODevice::ReadWrite | QIODevice::Text) )
					{
					if (fileManager->isOpen())
						fileManager->close();
					databaseChangeEvent(CurrentRecordCantOpen);
					return;
					}
				else
					{
					if ( fileHashMap.value(indexBuff) != QCryptographicHash::hash(fileManager->readAll(), QCryptographicHash::Md5).toHex() )
						{
						if (fileManager->isOpen())
							fileManager->close();
						databaseChangeEvent(CurrenRecordHashChanged);
						return;
						}
					else
						{
						if (fileManager->isOpen())
							fileManager->close();
						}
					}
				}

			}
		}
	}

