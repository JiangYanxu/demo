#include <sl_private.hpp>
#include <sl_public.hpp>
#include <dl.hpp>
#include <QDebug>
int main(int argc, char * argv[])
{
    qDebug() << "main start!";
    DL::hello();
    SLPrivate::hello();
    SLPublic::hello();
    qDebug() << "main done!";
    return 0;
}