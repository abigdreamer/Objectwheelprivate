#ifndef ZDATABASEMANAGER_H
#define ZDATABASEMANAGER_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QTimer>
#include <QMap>
#include <QFile>
#include <QCryptographicHash>
#include <QStringList>
#include <iostream>
#include <QDebug>

using namespace std;

#define CURRENTFILE "currentFile.ix"

class ZDatabaseManager : public QObject
	{
		Q_OBJECT
	private:
		enum DatabaseChangeEvents
			{
			CurrentFileDoesntExist,
			CurrentFileCantOpen,
			CurrentFileHashIsNull,
			CurrentFileIndexIsNull,
			CurrenFileIndexChanged,
			CurrentFileHashChanged,
			CurrentRecordDoesntExist,
			CurrentRecordCantOpen,
			CurrenRecordHashChanged,
			};

		int checkTimeout;
		int currentFileIndex;
		QString databaseDirectory, fileNameBody;
		QTimer* changeListenerTimer;
		QMap<int, QString> fileHashMap;
		QFile* fileManager;

		void databaseChangeEvent(const DatabaseChangeEvents event);
	public:
		explicit ZDatabaseManager(QObject *parent = 0);
		ZDatabaseManager(const QString& databasedirectory, const QString& filenamebody, const int msecond=1000);

		void setFileName(const QString& databasedirectory, const QString& filenamebody);
		void setCheckTimeout(const int msecond=1000);
		void setCurrentFileIndex(const int index);
		bool addFile(const QByteArray& file);
		bool removeFile();
		void startChangeListener();

		const QString& getFileName() const;
		const int& getCheckTimeout() const;
		const int& getCurrentFileIndex() const;
		QByteArray getFile() const;
		bool isChangeListenerActive() const;
		int getSize() const;

		~ZDatabaseManager();

	public slots:
		void changeListener();

	signals:
		void databaseChanged();
	};

#endif // ZDATABASEMANAGER_H
