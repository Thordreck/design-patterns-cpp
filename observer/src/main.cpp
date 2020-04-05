#include <vector>
#include <iostream>

#include "Observer.hpp"
#include "Observable.hpp"

// This is the observable
class Person : public Observable<Person>
{
    public:
        Person(int age) : age { age } {}

        int get_age() const
        {
            return age;
        }

        void set_age(int age)
        {
            if(this->age == age) { return; }

            this->age = age;
            notify(*this, "age");
        }

    private:
        int age;
};

// This is the observer
struct ConsolePersonObserver : public Observer<Person>
{
    void field_changed(Person& source, const std::string& field_name) override
    {
        std::cout << "Person's " << field_name << " has changed to ";

        if(field_name == "age")
        {
            std::cout << source.get_age() << std::endl;
        }
    }
};

int main()
{
    Person person { 10 };
    ConsolePersonObserver cpo;

    person.subscribe(cpo);

    person.set_age(11);
    person.set_age(12);

    person.unsubscribe(cpo);

    person.set_age(13);

    return 0;
}
