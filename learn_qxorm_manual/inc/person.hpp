#ifndef PERSON_HPP
#define PERSON_HPP

#include <export.hpp>
#include <QDateTime>
#include <QString>

class QX_MY_DEMO_EXPORT Person
{
public:
    uint64_t id;
    QString firstName;
    QString lastName;
    QDateTime birthDate;
    int age;
    Person() {}
    virtual ~Person() {}
};

QX_REGISTER_PRIMARY_KEY(Person, uint64_t)
QX_REGISTER_HPP_MY_DEMO(Person, qx::trait::no_base_class_defined, 0)

#endif // PERSON_HPP