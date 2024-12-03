#include <sl_private.hpp>
#include <sl_public.hpp>
#include <QDebug>

void SLPublic::hello() 
{
    qDebug() << "Hello from SLPublic!";
}

void SLPrivate::hello() 
{
    qDebug() << "Hello from SLPrivate!";
}