#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

class Person
{
    public:
        Person(std::string name);
        ~Person();

        void greet();

    private:
        std::string name;

        class PersonImpl;
        PersonImpl* impl;
};

#endif
