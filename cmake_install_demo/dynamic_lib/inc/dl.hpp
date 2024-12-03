#ifndef DL_HPP
#define DL_HPP

#include <QtCore/qglobal.h>

#if defined(BUILD_DL_LIB)
#  define DL_EXPORT Q_DECL_EXPORT
#else
#  define DL_EXPORT Q_DECL_IMPORT
#endif

class DL_EXPORT DL {
public:
    static void hello();
};

#endif // DL_HPP