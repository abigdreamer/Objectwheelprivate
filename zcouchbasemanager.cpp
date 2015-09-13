#include "zcouchbasemanager.h"

#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
JNIEnv* ZCouchbaseManager::CreateVM(JavaVM** jvm)
	{
	JNIEnv *env;
	JavaVMInitArgs vm_args;
	JavaVMOption* options = new JavaVMOption[2];
	options[0].optionString = (char*)"-Xbootclasspath/a:/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/java/classes";
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
	else
		qWarning("Java VM successfuly created!");
#endif
	}

bool ZCouchbaseManager::open()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetStaticMethodID(JEnv.jClass, "open", "()Z");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return false;
		}
	return JEnv.env->CallStaticBooleanMethod(JEnv.jClass, func);
#endif
	return false;
	}

int ZCouchbaseManager::docCount()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetStaticMethodID(JEnv.jClass, "docCount", "()I");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return false;
		}
	return JEnv.env->CallStaticBooleanMethod(JEnv.jClass, func);
#endif
	return -1;
	}

void ZCouchbaseManager::stopSync()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetStaticMethodID(JEnv.jClass, "stopSync", "()V");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return;
		}
	JEnv.env->CallStaticVoidMethod(JEnv.jClass, func);
#endif
	}

void ZCouchbaseManager::startSync()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetStaticMethodID(JEnv.jClass, "startSync", "()V");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return;
		}
	JEnv.env->CallStaticVoidMethod(JEnv.jClass, func);
#endif
	}

bool ZCouchbaseManager::delCurrentDoc()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetStaticMethodID(JEnv.jClass, "delCurrentDoc", "()Z");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return false;
		}
	return JEnv.env->CallStaticBooleanMethod(JEnv.jClass, func);
#endif
	return false;
	}

void ZCouchbaseManager::startChangeListener()
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetStaticMethodID(JEnv.jClass, "startChangeListener", "()V");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return;
		}
	JEnv.env->CallStaticVoidMethod(JEnv.jClass, func);
#endif
	}

const QString ZCouchbaseManager::getCurrentDoc()
	{
	QString ret;
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetStaticMethodID(JEnv.jClass, "getCurrentDoc", "()Ljava/lang/String;");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return 0;
		}
	jstring str=(jstring)JEnv.env->CallStaticObjectMethod(JEnv.jClass, func);

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

bool ZCouchbaseManager::addDoc(const QString& json)
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetStaticMethodID(JEnv.jClass, "addDoc", "(Ljava/lang/String;)Z");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return 0;
		}
	return JEnv.env->CallStaticBooleanMethod(JEnv.jClass, func,JEnv.env->NewStringUTF(json.toUtf8().constData()) );
#endif
	return false;
	}

bool ZCouchbaseManager::setCurrentDoc(const QString& id)
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetStaticMethodID(JEnv.jClass, "setCurrentDoc", "(Ljava/lang/String;)Z");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return 0;
		}
	return JEnv.env->CallStaticBooleanMethod(JEnv.jClass, func,JEnv.env->NewStringUTF(id.toUtf8().constData()) );
#endif
	return false;
	}

void ZCouchbaseManager::setDatabaseName(const QString& dbname)
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetStaticMethodID(JEnv.jClass, "setDatabaseName", "(Ljava/lang/String;)V");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return;
		}
	JEnv.env->CallStaticVoidMethod(JEnv.jClass, func,JEnv.env->NewStringUTF(dbname.toUtf8().constData()) );
#endif
	}

void ZCouchbaseManager::setHostAddress(const QString& haddress)
	{
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	jmethodID func=JEnv.env->GetStaticMethodID(JEnv.jClass, "setHostAddress", "(Ljava/lang/String;)V");
	if (func == 0)
		{
		qWarning("ZCouchbaseManager : Fail Get Static Method");
		return;
		}
	JEnv.env->CallStaticVoidMethod(JEnv.jClass, func,JEnv.env->NewStringUTF(haddress.toUtf8().constData()));
#endif
	}

