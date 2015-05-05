#include "zcouchbasemanager.h"

QByteArray ZCouchbaseManager::gotData=NULL;
bool ZCouchbaseManager::setedData=false;
bool ZCouchbaseManager::removedData=false;
/// Get operation callback
static void getCallBack(lcb_t instance, const void* cookie, lcb_error_t error, const lcb_get_resp_t* item)
	{
	if (error == LCB_SUCCESS)
		{
		ZCouchbaseManager::gotData=QByteArray::fromRawData((char*)item->v.v0.bytes,(int)item->v.v0.nbytes);
		}
	else
		{
		ZCouchbaseManager::gotData=NULL;
		Q_UNUSED(instance);
		//fprintf(stderr, "ZCouchbaseManager::callBackEvent() : %s. Received code 0x%X (%s)\n",
		//		"Couldn't retrieve", error, lcb_strerror(instance, error));
		}
	(void)cookie;
	}

/// Set operation callback
static void setCallBack(lcb_t , const void *,
						   lcb_storage_t operation, lcb_error_t error, const lcb_store_resp_t *)
	{
	if (error == LCB_SUCCESS) {
		ZCouchbaseManager::setedData=true;
		}
	else {
		ZCouchbaseManager::setedData=false;
		fprintf(stderr, "ZCouchbaseManager::setCallBack() : Failed to set item: \n");
		}
	(void)operation;
	}
/// Remove operation callback
static void removeCallBack(lcb_t instance, const void *, lcb_error_t err,
						   const lcb_remove_resp_t *)
	{
	if (err != LCB_SUCCESS) {
		ZCouchbaseManager::removedData=false;
		fprintf(stderr, "ZCouchbaseManager::removeCallBack() : Failed to remove item: %s\n", lcb_strerror(instance, err));
		}
	else
		ZCouchbaseManager::removedData=true;
	}

ZCouchbaseManager::ZCouchbaseManager(QObject *parent) :
	QObject(parent)
	{
	}

bool ZCouchbaseManager::connectBucket(const QString& bucket, const QString& password)
	{
	/// Setting host information
	create_options.version = 3;
	create_options.v.v3.connstr = bucket.toStdString().c_str();
	create_options.v.v3.passwd = password.toStdString().c_str();
	err = lcb_create(&instance, &create_options);
	if (err != LCB_SUCCESS)
		{
		fprintf(stderr, "ZCouchbaseManager::connectBucket() : %s. Received code 0x%X (%s)\n",
				"Couldn't create couchbase handle", err, lcb_strerror(NULL, err));
		return false;
		}

	lcb_U32 timeout = 5000000;
	lcb_cntl(instance, LCB_CNTL_SET, LCB_CNTL_OP_TIMEOUT, &timeout);
	lcb_cntl(instance, LCB_CNTL_GET, LCB_CNTL_OP_TIMEOUT, &timeout);
	/// Connecting
	err = lcb_connect(instance);
	if (err != LCB_SUCCESS)
		{
		fprintf(stderr, "ZCouchbaseManager::connectBucket() : %s. Received code 0x%X (%s)\n",
				"Couldn't schedule connection", err, lcb_strerror(instance, err));
		return false;
		}
	lcb_wait(instance);

	/// Bootstraping
	err = lcb_get_bootstrap_status(instance);
	if (err != LCB_SUCCESS)
		{
		fprintf(stderr, "ZCouchbaseManager::connectBucket() : %s. Received code 0x%X (%s)\n",
				"Couldn't bootstrap from cluster", err, lcb_strerror(instance, err));
		return false;
		}
	return true;
	}

QByteArray* ZCouchbaseManager::getData(const QString& ID, const lcb_get_callback& callBack)
	{
	/// Setting getCallBack
	if (callBack!=NULL)
		lcb_set_get_callback(instance,callBack);
	else
		lcb_set_get_callback(instance,getCallBack);

	/// Getting data
	gcmd.v.v0.key = ID.toStdString().c_str();
	gcmd.v.v0.nkey = ID.size();
	gcmdlist[0] = &gcmd;
	err = lcb_get(instance, NULL, 1, gcmdlist);
	if (err != LCB_SUCCESS)
		{
		fprintf(stderr, "ZCouchbaseManager::getData() : %s. Received code 0x%X (%s)\n",
				"Couldn't schedule retrieval operation", err, lcb_strerror(instance, err));
		return NULL;
		}
	lcb_wait(instance);

	/// If it's fail, returning &NULL(nullptr), otherwise returning got data ptr
	return &gotData;
	}

bool ZCouchbaseManager::removeData(const QString& ID, const lcb_remove_callback& callBack)
	{
	/// Setting setCallBack
	if (callBack!=NULL)
		lcb_set_remove_callback(instance, callBack);
	else
		lcb_set_remove_callback(instance, removeCallBack);


	lcb_remove_cmd_t cmd;
	const lcb_remove_cmd_t *cmdlist = &cmd;
	cmd.v.v0.key = ID.toStdString().c_str();
	cmd.v.v0.nkey = ID.size();
	err = lcb_remove(instance, NULL, 1, &cmdlist);
	if (err != LCB_SUCCESS) {
		printf("ZCouchbaseManager::removeData() : Couldn't schedule remove operation: %s\n", lcb_strerror(instance, err));
		return false;
		}
	lcb_wait(instance);
	/// If it's fail, returning false, otherwise true
	return removedData;
	}

bool ZCouchbaseManager::setData(const QString& ID, const QByteArray& data, const lcb_store_callback& callBack)
	{
	/// Setting setCallBack
	if (callBack!=NULL)
		lcb_set_store_callback(instance, callBack);
	else
		lcb_set_store_callback(instance, setCallBack);

	/// Setting data3
	scmd.v.v0.operation = LCB_SET;
	scmd.v.v0.key = ID.toStdString().c_str(); scmd.v.v0.nkey = ID.size();
	scmd.v.v0.bytes = data.constData(); scmd.v.v0.nbytes = data.size();
	scmdlist[0] = &scmd;
	err = lcb_store(instance, NULL, 1, scmdlist);
	if (err != LCB_SUCCESS)
		{
		fprintf(stderr, "ZCouchbaseManager::setData() : %s. Received code 0x%X (%s)\n",
				"Couldn't schedule storage operation", err, lcb_strerror(instance, err));
		return false;
		}
	lcb_wait(instance);
	/// If it's fail, returning false, otherwise true
	return setedData;
	}

/// For controlling bucket for a ID(file) is exist.
bool ZCouchbaseManager::isIdExist(const QString& ID,const QString& bucketAddress,const QString& bucketPassword )
	{
	/// connecting bucket with ZCouchbaseManager
	if (!this->connectBucket(bucketAddress, bucketPassword))
		return false;

	/// For controlling bucket for a ID(file) is exist.
    if ( *(this->getData(ID)) == (QByteArray)NULL)
		return false;
	else
		return true;
	}

void ZCouchbaseManager::waitForRequest()
	{
	lcb_wait(instance);
	}


ZCouchbaseManager::~ZCouchbaseManager()
	{
	lcb_destroy(instance);
	}
