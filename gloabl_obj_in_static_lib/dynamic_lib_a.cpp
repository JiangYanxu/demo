#include <dynamic_lib_a.hpp>
#include <static_lib.hpp>
#include <QDebug>

void A::show_one()
{
    qDebug() << StaticLib::get(0);
    // qDebug() << StaticLib::vecs.vecs.size();
}
