#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "Person.hpp"
#include "PersonBuilder.hpp"
#include "PersonAddressBuilder.hpp"
#include "PersonJobBuilder.hpp"

int main()
{
    Person p = Person::create()
        .lives().at("123 London Road")
                .with_postcode("SW1 1GB")
                .in("London")
        .works().at("PragmaSoft")
                .as_a("Consultant")
                .earning(10e6);

    std::cout << p << std::endl;

    return 0;
}
