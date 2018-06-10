
#ifndef CDL_GLOBAL_H
#define CDL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CDL_LIBRARY)
#  define CDLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CDLSHARED_EXPORT Q_DECL_IMPORT
#endif

#if defined(CDL_LIBRARY)
#  define POLYGON_LIBRARY Q_DECL_EXPORT
#else
#  define POLYGON_LIBRARY Q_DECL_IMPORT
#endif

#endif // CDL_GLOBAL_H
