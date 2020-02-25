#ifndef DRINK_FACTORY_HPP
#define DRINK_FACTORY_HPP

#include <map>
#include <memory>
#include <string>

#include "HotDrink.hpp"
#include "HotDrinkFactory.hpp"

class DrinkFactory
{
    public:
        DrinkFactory()
        {
            hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
            hot_factories["tea"]    = std::make_unique<TeaFactory>();
        }

        std::unique_ptr<HotDrink> make_drink(const std::string& drink)
        {
            auto prepared_drink = hot_factories.at(drink)->make();
            prepared_drink->prepare(200);

            return prepared_drink;
        }

    private:
        std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;
};

#endif
