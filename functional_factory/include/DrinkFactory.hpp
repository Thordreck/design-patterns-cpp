#ifndef DRINK_FACTORY_HPP
#define DRINK_FACTORY_HPP

#include <map>
#include <memory>
#include <string>
#include <functional>

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

class DrinkWithVolumeFactory
{
    public:
        DrinkWithVolumeFactory()
        {
            factories["tea"] = [] {
                auto tea = std::make_unique<Tea>();
                tea->prepare(200);
                return tea;
            };
        }

        std::unique_ptr<HotDrink> make_drink(const std::string& name)
        {
            return factories.at(name)();
        }

    private:
        std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;
};

#endif
