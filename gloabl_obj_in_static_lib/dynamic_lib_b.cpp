#include <dynamic_lib_b.hpp>
#include <static_lib.hpp>
#include <QDebug>

void B::show_two()
{
    qDebug() << StaticLib::get(1);
    // qDebug() << StaticLib::vecs.vecs.size();
}
