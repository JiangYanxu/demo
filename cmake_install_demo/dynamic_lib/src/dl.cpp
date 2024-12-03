#include "dl.hpp"
#include <QDebug>

void DL::hello() {
    qDebug() << "Hello from dynamic library!";
}
