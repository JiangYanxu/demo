#ifndef DYNAMIC_LIB_B_HPP
#define DYNAMIC_LIB_B_HPP

#include <QtCore/qglobal.h>

#if defined(B_LIBRARY)
#define B_EXPORT Q_DECL_EXPORT
#else
#define B_EXPORT Q_DECL_IMPORT
#endif

class B_EXPORT B
{
public:
    void show_two();
};

#endif // DYNAMIC_LIB_B_HPP