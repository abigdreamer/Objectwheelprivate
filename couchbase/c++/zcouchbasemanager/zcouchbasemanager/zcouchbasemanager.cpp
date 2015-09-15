#include "zcouchbasemanager.h"
ZCouchbaseManager* mContext;
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
extern "C"{
JNIEXPORT void JNICALL Java_syncgateway_ZDatabaseLayer_changedNativeCallBack
(JNIEnv *, jobject)
	{
	mContext->receivedDataHandler();
	}
}

JNIEnv* ZCouchbaseManager::CreateVM(JavaVM** jvm)
	{
	JNIEnv *env;
	JavaVMInitArgs vm_args;
	JavaVMOption* options = new JavaVMOption[2];
	options[0].optionString = (char*)"-Djava.class.path=/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/commons-logging-1.1.3.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/couchbase-lite-java-1.1.0.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/couchbase-lite-java-core.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/couchbase-lite-java-core-1.1.0.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/couchbase-lite-java-native.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/couchbase-lite-java-native-1.1.0.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/couchbase-lite-java-native-sources.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/doclet.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/httpclient-4.0-beta1.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/httpcore-4.0-beta2.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/jackson-annotations-2.5.0.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/jackson-core-2.5.0.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/jackson-databind-2.5.0.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/lib/stateless4j-2.4.0.jar:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/classes";
	vm_args.version = JNI_VERSION_1_6;
	vm_args.nOptions = 1;
	vm_args.options = options;
	vm_args.ignoreUnrecognized = false;
	JNI_CreateJavaVM(jvm, (void**)&env, &vm_args);
	delete options;
	return env;
	}
#endif

ZCouchbaseManager::ZCouchbaseManager(QObject *parent) : QObject(parent)
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	mContext=this;
	JEnv.env = CreateVM(&JEnv.jvm);
	if(JEnv.env == NULL)
		{
		qWarning("ZCouchbaseManager : Java VM wasn't created!");
		exit(1);
		}
	JEnv.jClass = JEnv.env->FindClass("syncgateway/ZDatabaseLayer");
	if (JEnv.jClass == 0)
		{
		qWarning("ZCouchbaseManager : Fail Find Class");
		exit(1);
		}

	jmethodID constructor=JEnv.env->GetMethodID(JEnv.jClass, "<init>", "()V");
	if (constructor == 0)
		qWarning("ZCouchbaseManager : Find method Failed");

	JEnv.jObject=JEnv.env->NewObject(JEnv.jClass,constructor);
	if (constructor == 0)
		qWarning("ZCouchbaseManager : Contruct method Failed");
	else
		qWarning("Java VM successfuly created!");
#endif
	}

bool ZCouchbaseManager::open()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "open", "()Z");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return false;
		}
	return JEnv.env->CallBooleanMethod(JEnv.jObject, func);
#endif
	return false;
	}

int ZCouchbaseManager::docCount()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "docCount", "()I");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return false;
		}
	return JEnv.env->CallIntMethod(JEnv.jObject, func);
#endif
	return -1;
	}

void ZCouchbaseManager::stopSync()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "stopSync", "()V");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return;
		}
	JEnv.env->CallVoidMethod(JEnv.jObject, func);
#endif
	}

void ZCouchbaseManager::startSync()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "startSync", "()V");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return;
		}
	JEnv.env->CallVoidMethod(JEnv.jObject, func);
#endif
	}

bool ZCouchbaseManager::delCurrentDoc()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "delCurrentDoc", "()Z");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return false;
		}
	return JEnv.env->CallBooleanMethod(JEnv.jObject, func);
#endif
	return false;
	}

int ZCouchbaseManager::getCurrentDocId()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "getCurrentDocId", "()I");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return false;
		}
	return JEnv.env->CallIntMethod(JEnv.jObject, func);
#endif
	return -1;
	}

void ZCouchbaseManager::startChangeListener()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "startChangeListener", "()V");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return;
		}
	JEnv.env->CallVoidMethod(JEnv.jObject, func);
#endif
	}

const QString ZCouchbaseManager::getCurrentDoc()
	{
	QString ret;
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "getCurrentDoc", "()Ljava/lang/String;");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return 0;
		}
	jstring str=(jstring)JEnv.env->CallObjectMethod(JEnv.jObject, func);

	if (str != 0)
		{
		// Now convert the Java String to C++ char array
		const char* cstr = JEnv.env->GetStringUTFChars(str, 0);
		ret=QString::fromUtf8(cstr);
		JEnv.env->ReleaseStringUTFChars(str,cstr);
		JEnv.env->DeleteLocalRef(str);
		}
#endif
	return ret;
	}
#include <QFile>
bool ZCouchbaseManager::addDoc(QString json)
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "addDoc", "(Ljava/lang/String;)Z");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return 0;
		}
	return JEnv.env->CallBooleanMethod(JEnv.jObject, func,JEnv.env->NewStringUTF(json.toUtf8().constData()) );
#endif
	return false;
	}

bool ZCouchbaseManager::setCurrentDoc(const int id)
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "setCurrentDoc", "(Ljava/lang/String;)Z");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return 0;
		}
	return JEnv.env->CallBooleanMethod(JEnv.jObject, func,JEnv.env->NewStringUTF(QString::number(id).toUtf8().constData()) );
#endif
	return false;
	}

void ZCouchbaseManager::setDatabaseName(const QString& dbname)
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "setDatabaseName", "(Ljava/lang/String;)V");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return;
		}
	JEnv.env->CallVoidMethod(JEnv.jObject, func,JEnv.env->NewStringUTF(dbname.toUtf8().constData()) );
#endif
	}

void ZCouchbaseManager::setHostAddress(const QString& haddress)
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetMethodID(JEnv.jClass, "setHostAddress", "(Ljava/lang/String;)V");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return;
		}
	JEnv.env->CallVoidMethod(JEnv.jObject, func,JEnv.env->NewStringUTF(haddress.toUtf8().constData()));
#endif
	}

