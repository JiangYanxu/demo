#include <dynamic_lib_a.hpp>
#include <dynamic_lib_b.hpp>
#include <QDebug>

A a;
B b;
int main()
{
    qDebug() << "main begin!";
    a.show_one();
    b.show_two();
    qDebug() << "main end!";
    return 0;
}
