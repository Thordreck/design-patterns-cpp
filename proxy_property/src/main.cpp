#include <string>
#include <sstream>
#include <iostream>

template <typename T>
struct Property
{
    T value;

    Property(T value)
    {
        *this = value;
    }

    operator T()
    {
        return value;
    }

    T operator=(T new_value)
    {
        std::cout << "Assigning value" << std::endl;
        return value = new_value;
    }
};

struct Creature
{
    Property<int> strength { 10 };
    Property<int> agility  { 10 };
};

int main()
{
    Creature c;
    c.strength = 15;

    return 0;
}
