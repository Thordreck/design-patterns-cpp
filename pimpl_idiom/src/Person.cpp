#include <iostream>

#include "Person.hpp"

class Person::PersonImpl
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
    : name( std::move(name) ),
      impl( new PersonImpl )
{}

Person::~Person() 
{
    delete impl;
}

void Person::greet()
{
    impl->greet(this);
}
