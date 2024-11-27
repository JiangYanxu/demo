#ifndef DYNAMIC_LIB_A_HPP
#define DYNAMIC_LIB_A_HPP

#include <QtCore/qglobal.h>

#if defined(A_LIBRARY)
#define A_EXPORT Q_DECL_EXPORT
#else
#define A_EXPORT Q_DECL_IMPORT
#endif

class A_EXPORT A
{
public:
    void show_one();
};

#endif // DYNAMIC_LIB_A_HPP