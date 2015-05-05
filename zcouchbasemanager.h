#ifndef ZCouchbaseManager_H
#define ZCouchbaseManager_H

#include <QObject>
#include <stdio.h>
#include <libcouchbase/couchbase.h>
#include <QString>
#include <QByteArray>
#include <QtCore>
#include <QThread>

using namespace std;

class ZCouchbaseManager : public QObject
	{
		Q_OBJECT
	private:
		lcb_error_t err;
		lcb_t instance;
		struct lcb_create_st create_options;
		lcb_get_cmd_t gcmd ;
		const lcb_get_cmd_t *gcmdlist[1];
		lcb_store_cmd_t scmd;
		const lcb_store_cmd_t *scmdlist[1];

		const QString bucketName, bucketPass;
		

	public:
		explicit ZCouchbaseManager(QObject *parent = 0);

		QByteArray* getData(const QString& ID, const lcb_get_callback& callBack=NULL);
		bool removeData(const QString& ID, const lcb_remove_callback& callBack=NULL);
		bool setData(const QString& ID, const QByteArray& data, const lcb_store_callback& callBack=NULL);
		bool isIdExist(const QString& ID, const QString& bucketAddress, const QString& bucketPassword);
		void waitForRequest();
		bool connectBucket(const QString& bucket, const QString& password);
		
		

		static QByteArray gotData;
		static bool setedData;
		static bool removedData;
		~ZCouchbaseManager();
	signals:

	public slots:

	};

#endif // ZCouchbaseManager_H
