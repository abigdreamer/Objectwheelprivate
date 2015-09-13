#ifndef ZCOUCHBASEMANAGER_H
#define ZCOUCHBASEMANAGER_H

#include <QObject>

#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
#include <jni.h>
struct ZJavaEnvForPc
	{
		JavaVM *jvm;
		JNIEnv *env;
		jclass jClass;
		jobject jObject;
	};
#endif

class ZCouchbaseManager : public QObject
	{
		Q_OBJECT
	private:
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
		ZJavaEnvForPc JEnv;
		JNIEnv* CreateVM(JavaVM** jvm);
#endif
	public:
		explicit ZCouchbaseManager(QObject *parent = 0);

		bool open();
		int docCount();
		void stopSync();
		void startSync();
		bool delCurrentDoc();
		int getCurrentDocId();
		void startChangeListener();
		const QString getCurrentDoc();
		bool addDoc( const QString& json );
		bool setCurrentDoc( const int id );
		void setDatabaseName( const QString& dbname );
		void setHostAddress( const QString& haddress );

		void receivedDataHandler()
			{ emit databaseChanged(); }
	signals:
		void databaseChanged();
	public slots:
	};

#endif // ZCOUCHBASEMANAGER_H
