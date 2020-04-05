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

            const bool old_can_vote = get_can_vote();

            this->age = age;
            notify(*this, "age");

            if(old_can_vote != get_can_vote())
            {
                notify(*this, "can_vote");
            }
        }

        // This is difficult to subscribe to, since we don't really
        // have a setter.
        bool get_can_vote() const
        {
            return age >= 16;
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
        else if(field_name == "can_vote")
        {
            std::cout << std::boolalpha << source.get_can_vote() << std::endl;
        }
    }
};

int main()
{
    Person person { 10 };
    ConsolePersonObserver cpo;

    person.subscribe(cpo);

    person.set_age(15);
    person.set_age(16);

    return 0;
}
