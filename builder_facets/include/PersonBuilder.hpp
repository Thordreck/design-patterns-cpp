#ifndef PERSON_BUILDER_HPP
#define PERSON_BUILDER_HPP

#include "Person.hpp"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
    public:
        PersonBuilderBase(Person& person);

        operator Person() const { return person; }

        PersonAddressBuilder lives() const;
        PersonJobBuilder works() const;

    protected:
        Person& person;
};

class PersonBuilder : public PersonBuilderBase
{
    public:
        PersonBuilder();

    private:
        Person p;
};

#endif
