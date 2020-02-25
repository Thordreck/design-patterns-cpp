#ifndef HOT_DRINK_FACTORY_HPP
#define HOT_DRINK_FACTORY_HPP

#include <memory>
#include <iostream>

#include "HotDrink.hpp"

// Abstract factory
struct HotDrinkFactory
{
    virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : public HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Tea>();
    }
};

struct CoffeeFactory : public HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Coffee>();
    }
};

#endif
