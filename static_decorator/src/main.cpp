#include <string>
#include <sstream>
#include <iostream>

struct Shape
{
    virtual std::string str() const = 0;
};

struct Circle : public Shape
{
    float radius;

    Circle() = default;
    Circle(float radius) : radius(radius) {}

    void resize(float factor)
    {
        radius *= factor;
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A circle of radius " << radius;

        return oss.str();
    }
};

struct Square : public Shape
{
    float side;

    Square() = default;
    Square(float side) : side(side) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A square of side " << side;

        return oss.str();
    }
};

// This is the dynamic decorators implementation
struct ColoredShape : Shape
{
    Shape& shape;
    std::string color;

    ColoredShape(Shape& shape, std::string color)
        : shape(shape)
        , color(std::move(color))
    {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;

        return oss.str();
    }
};

struct TransparentShape : Shape
{
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape, uint8_t transparency)
        : shape(shape)
        , transparency(transparency)
    {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str()
            << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";

        return oss.str();
    }
};


// And this is the static version in compile time
template <typename T>
struct ColoredShape2 : T
{
    static_assert(std::is_base_of<Shape, T>::value,
                  "Template argument must be a Shape");

    std::string color;

    ColoredShape2() = default;

    // Note: here we are taking the argument we are interested on
    // (in this case, the color) and we forward the rest to the
    // parent's constructor. Note this allow us to chain
    // together multiple shapes, and just pass all the arguments to
    // the constructor of the resulting object.
    template <typename ...Args>
    ColoredShape2(std::string color, Args ...args)
        : T(std::forward<Args>(args)...)
        , color { color }
    {}

    std::string str() const override
    {
        std::ostringstream oss;

        oss << T::str() << " has the color " << color;

        return oss.str();
    }
};

template <typename T>
struct TransparentShape2 : T
{
    static_assert(std::is_base_of<Shape, T>::value,
                  "Template argument must be a Shape");

    uint8_t transparency;

    TransparentShape2() = default;

    // Note: here we are taking the argument we are interested on
    // (in this case, the transparency) and we forward the rest to the
    // parent's constructor. Note this allow us to chain
    // together multiple shapes, and just pass all the arguments to
    // the constructor of the resulting object.
    template <typename ...Args>
    TransparentShape2(uint8_t transparency, Args ...args)
        : T(std::forward<Args>(args)...)
        , transparency { transparency }
    {}

    std::string str() const override
    {
        std::ostringstream oss;

        oss << T::str()
            << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";

        return oss.str();
    }
};

int main()
{
    ColoredShape2<Circle> green_circle { "green", 5 };

    // Note that with static decorators, it's possible to call methods
    // of the original shape, as we are using inheritance, instead of
    // aggregation.
    green_circle.resize(2);
    std::cout << green_circle.str() << std::endl;

    // We can also combined together multiple decorators. Note that
    // the arguments in the constructor must follow the same order
    // in which the template arguments are chained up together.
    TransparentShape2<ColoredShape2<Square>> square { 51, "blue", 10 };
    std::cout << square.str() << std::endl;

    return 0;
}
