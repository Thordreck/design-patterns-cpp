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

int main()
{
    Square square { 5 };
    ColoredShape red_square(square, "red");

    std::cout << square.str() << std::endl;
    std::cout << red_square.str() << std::endl;

    TransparentShape transparent_square { red_square, 51 };

    std::cout << transparent_square.str() << std::endl;

    return 0;
}
