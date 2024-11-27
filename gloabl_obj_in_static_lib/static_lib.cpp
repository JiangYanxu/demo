#include <static_lib.hpp>
#include <QDebug>
#include <QThread>

// const std::vector<QString> StaticLib::vecs = { "A", "B", "C", "D", "E", };
// const std::vector<QQString> StaticLib::vecs{ {"A"}, {"B"} };
//  const Vec StaticLib::vecs({ {"MMM"}, {"NNN"} });
//const Vec StaticLib::vecs({});

char const * const vecs[] = {"123", "111"};

QString StaticLib::get(int i)
{
    // vecs = 1;
    // vecs[i][0] = 1;
    // vecs[i] = vecs[i+1];
    return vecs[i];
    // return vecs.at(i);
}

QQString::QQString(const QString &s)
{
    qDebug() << s << this; 
    this->s = s;
}
QQString::~QQString()
{
    qDebug() << "~QQString" << this;
}
Vec::Vec(const std::vector<QQString> v)
{
    qDebug() << "VEC:" << this; 
    this->vecs = v;
}
Vec::~Vec()
{
    this->vecs.clear();
    qDebug() << "Vec~" << this;
    qDebug() << "Vec~QThread" << QThread::currentThreadId();
}
