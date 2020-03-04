#include <string>
#include <vector>
#include <iostream>

struct GraphicObject
{
    virtual void draw() = 0;
};

struct Circle : public GraphicObject
{
    void draw() override
    {
        std::cout << "Circle" << std::endl;
    }
};

struct Group : public GraphicObject
{
    Group(std::string _name) : name(_name) {}

    void draw() override
    {
        std::cout << "Group " << name << " contains: " << std::endl;

        for(auto&& o : objects)
        {
            o->draw();
        }
    }

    std::vector<GraphicObject*> objects;
    std::string name;
};

int main()
{
    Group root("root");
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);
    root.draw();

    return 0;
}
