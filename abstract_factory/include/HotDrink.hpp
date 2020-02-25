#ifndef HOT_DRINK_HPP
#define HOT_DRINK_HPP

#include <iostream>

struct HotDrink
{
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

struct Tea : public HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "Take tea bag, boil water, pour " << volume
            << "ml, add some lemon" << std::endl;
    }
};

struct Coffee : public HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "Grind some beans, boil water, pour " << volume
            << "ml, add cream and enjoy!" << std::endl;
    }
};

#endif
