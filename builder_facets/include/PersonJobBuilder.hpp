#ifndef PERSON_JOB_BUILDER_HPP
#define PERSON_JOB_BUILDER_HPP

#include <string>

#include "PersonBuilder.hpp"

class PersonJobBuilder : public PersonBuilderBase
{
    public:
        PersonJobBuilder(Person& person) : PersonBuilderBase(person) {}

        PersonJobBuilder& at(const std::string& company_name)
        {
            person.company_name = company_name;
            return *this;
        }

        PersonJobBuilder& as_a(const std::string& position)
        {
            person.position = position;
            return *this;
        }

        PersonJobBuilder& earning(int annual_income)
        {
            person.annual_income = annual_income;
            return *this;
        }
};

#endif
