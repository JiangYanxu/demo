#ifndef STATIC_LIB_HPP
#define STATIC_LIB_HPP

#include <QString>
#include <QObject>
#include <vector>

struct QQString
{
    QString s;
    QQString(const QString &s);
    ~QQString();
};
struct Vec
{
    std::vector<QQString> vecs;
    Vec(const std::vector<QQString> v);
    ~Vec();
};

class StaticLib : public QObject
{
    Q_OBJECT
public:
    static QString get(int i);

    // static const std::vector<const char *> vecs; 
    // static const Vec vecs;
    // static const std::vector<QQString> vecs;
};

#endif // STATIC_LIB_HPP
