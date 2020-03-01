#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

#include "pimpl.hpp"

class Person
{
    public:
        Person(std::string name);
        ~Person();

        void greet();

    private:
        std::string name;

        class impl;
        pimpl<impl> impl;
};

#endif
