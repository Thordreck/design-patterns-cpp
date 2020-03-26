#include <string>
#include <sstream>
#include <iostream>
#include <memory>

struct Image
{
    virtual void draw() = 0;
};

struct Bitmap : public Image
{
    Bitmap(const std::string& filename)
    {
        std::cout << "Loading bitmap from " << filename << std::endl;
    }

    void draw() override
    {
        std::cout << "Drawing bitmap" << std::endl;
    }
};

struct LazyBitmap : public Image
{
    LazyBitmap(const std::string filename)
        : filename(filename)
    {}

    void draw() override
    {
        if(!bitmap)
        {
            bitmap = std::make_unique<Bitmap>(filename);
        }

        bitmap->draw();
    }

    private:
        std::string filename;
        std::unique_ptr<Bitmap> bitmap;
};

int main()
{
    //Bitmap bmp { "pokemon.png" };
    LazyBitmap bmp { "pokemon.png" };
    bmp.draw();

    return 0;
}
