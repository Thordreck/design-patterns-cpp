#include <iostream>

struct Renderer
{
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : public Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        std::cout << "Rasterizing a circle of radius " << radius << std::endl;
    }
};

struct RasterRenderer : public Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        std::cout << "Rasterizing a vector circle of radius " << radius << std::endl;
    }
};

struct Shape
{
    public:
        virtual void draw() = 0;
        virtual void resize(float factor) = 0;

    protected:
        Shape(Renderer& renderer) : renderer(renderer) {}

    protected:
        Renderer& renderer;
};

struct Circle : public Shape
{
    public:
        Circle(Renderer& renderer, float x, float y, float radius)
            : Shape(renderer)
            , x (x)
            , y (y)
            , radius (radius)
        {}

        void draw() override
        {
            renderer.render_circle(x, y, radius);
        }

        void resize(float factor) override
        {
            radius *= factor;
        }

    private:
        float x;
        float y;
        float radius;
};

int main(int argc, char* argv[])
{
    RasterRenderer raster_render;

    Circle raster_circle { raster_render, 5, 5, 5 };
    raster_circle.draw();
    raster_circle.resize(2);
    raster_circle.draw();

    return 0;
}
