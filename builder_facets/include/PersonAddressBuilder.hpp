#ifndef PERSON_ADDRESS_BUILDER_HPP
#define PERSON_ADDRESS_BUILDER_HPP

#include <string>

#include "PersonBuilder.hpp"

class PersonAddressBuilder : public PersonBuilderBase
{
    public:
        PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}

        PersonAddressBuilder& at(const std::string& street_address)
        {
            person.street_address = street_address;
            return *this;
        }

        PersonAddressBuilder& with_postcode(const std::string& post_code)
        {
            person.post_code = post_code;
            return *this;
        }

        PersonAddressBuilder& in(const std::string& city)
        {
            person.city = city;
            return *this;
        }
};

#endif
