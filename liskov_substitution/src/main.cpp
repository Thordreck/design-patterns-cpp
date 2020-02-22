#include <iostream>
#include <algorithm>

class Rectangle
{
    public:
        Rectangle(int _width, int _height) : width_(_width), height_(_height) {}

        int get_width()  const { return width_;  }
        int get_height() const { return height_; }

        virtual void set_width(int _new_width)   { width_ = _new_width;   }
        virtual void set_height(int _new_height) { height_ = _new_height; }

        int area() const { return width_ * height_; }

    protected:
        int width_;
        int height_;
};

class Square : public Rectangle
{
    public:
        Square(int _size) : Rectangle(_size, _size) {}

        void set_width(int _new_width)   override { width_ = _new_width;  height_ = _new_width;  }
        void set_height(int _new_height) override { width_ = _new_height; height_ = _new_height; }
};

void process(Rectangle& _rectangle)
{
    const int width = _rectangle.get_width();

    _rectangle.set_height(10);

    std::cout << "Expected area = " << width * 10
              << ", got " << _rectangle.area() << std::endl;
}

int main()
{
    Rectangle r { 3, 4 };
    process(r);

    Square sq { 5 };
    process(sq);

    return 0;
}
