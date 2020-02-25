#include <string>

#include "HotDrinkFactory.hpp"
#include "DrinkFactory.hpp"

std::unique_ptr<HotDrink> make_drink_bad(const std::string& type)
{
    std::unique_ptr<HotDrink> drink;

    if(type == "tea")
    {
        drink = std::make_unique<Tea>();
        drink->prepare(200);
    }
    else if(type == "coffee")
    {
        drink = std::make_unique<Coffee>();
        drink->prepare(50);
    }

    return drink;
}

int main()
{
    auto d = make_drink_bad("tea");

    DrinkFactory drink_factory;
    auto c = drink_factory.make_drink("coffee");

    return 0;
}
