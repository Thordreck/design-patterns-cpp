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

class Person2 : public Observable2<Person2>
{
    public:
        Person2(int age) : age { age } {}

        int get_age() const
        {
            return age;
        }

        void set_age(int age)
        {
            if(this->age == age) { return; }

            this->age = age;

            field_changed(*this, "age");
        }

    private:
        int age;
};

int main()
{
    Person2 p2 { 11 };

    auto conn = p2.field_changed.connect(
            [] (Person2& p, const std::string& field_name)
            {
                std::cout << field_name << " has changed\n";
            });

    p2.set_age(20);
    conn.disconnect();

    return 0;
}
