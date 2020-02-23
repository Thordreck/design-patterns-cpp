#include <cmath>
#include <iostream>

class Point
{
    public:
        friend std::ostream& operator<<(std::ostream& os, const Point& point)
        {
            os << "x: " << point.x << " y: " << point.y;
            return os;
        }

    private:
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

    public:
        static PointFactory Factory;

    private:
        Point(double x, double y) : x(x), y(y) {}

    private:
        double x;
        double y;
};

int main()
{
    auto p = Point::Factory.NewPolar(5, M_PI_4);
    std::cout << p << std::endl;

    return 0;
}
