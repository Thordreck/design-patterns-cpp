#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <iostream>

class PersonBuilder;

class Person
{
    public:
        static PersonBuilder create();

        friend std::ostream& operator<<(std::ostream& os, const Person& obj)
        {
            return os
                << "street_address: " << obj.street_address
                << " post_code: " << obj.post_code
                << " city: " << obj.city
                << " company_name: " << obj.company_name
                << " position: " << obj.position
                << " annual_income: " << obj.annual_income;
        }

    private:
        // address
        std::string street_address;
        std::string post_code;
        std::string city;

        // employment
        std::string company_name;
        std::string position;

        int annual_income {};

        friend class PersonBuilder;
        friend class PersonJobBuilder;
        friend class PersonAddressBuilder;

};
#endif
