#include <iostream>

#include "Person.hpp"

class Person::impl
{
    public:
        void greet(Person *p)
        {
            std::cout << "Hello, my name is "
                      << p->name
                      << std::endl;
        }
};

Person::Person(std::string name) 
    : name( std::move(name) )
{}

Person::~Person() 
{}

void Person::greet()
{
    impl->greet(this);
}
