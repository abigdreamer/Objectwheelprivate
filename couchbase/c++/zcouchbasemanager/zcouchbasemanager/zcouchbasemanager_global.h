#ifndef ZCOUCHBASEMANAGER_GLOBAL_H
#define ZCOUCHBASEMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ZCOUCHBASEMANAGER_LIBRARY)
#  define ZCOUCHBASEMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ZCOUCHBASEMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ZCOUCHBASEMANAGER_GLOBAL_H