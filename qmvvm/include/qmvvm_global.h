#ifndef IZM_QMVVM_GLOBAL_H
#define IZM_QMVVM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IZM_QMVVM_LIBRARY)
#  define IZMQMVVMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define IZMQMVVMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // IZM_QMVVM_GLOBAL_H
