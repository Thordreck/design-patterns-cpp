#include <cmath>
#include <iostream>

class Point
{
    friend class PointFactory;

    public:
        friend std::ostream& operator<<(std::ostream& os, const Point& point)
        {
            os << "x: " << point.x << " y: " << point.y;
            return os;
        }

    private:
        Point(double x, double y) : x(x), y(y) {}

    private:
        double x;
        double y;
};

struct PointFactory
{
    static Point NewCartesian(double x, double y)
    {
        return { x, y };
    }

    static Point NewPolar(double r, double theta)
    {
        return { r * cos(theta), r * sin(theta) };
    }
};

int main()
{
    auto p = PointFactory::NewPolar(5, M_PI_4);
    std::cout << p << std::endl;

    return 0;
}
