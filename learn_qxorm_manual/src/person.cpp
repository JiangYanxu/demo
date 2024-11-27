#include <person.hpp>

QX_REGISTER_CPP_MY_DEMO(Person)

namespace qx {
    template <> void register_class(QxClass<Person> &t)
    {
        t.setName("t_Person");
        t.id(&Person::id, "id");
        t.data(&Person::firstName, "firstName");
        t.data(&Person::lastName, "lastName");
        t.data(&Person::birthDate, "birthDate");
        // t.data(&Person::age, "age", 0, true, false);
        auto *pDataMember = t.data(&Person::age, "age");
        pDataMember->setDao(false);
    }
}


