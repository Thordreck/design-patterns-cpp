#include <iostream>
#include <sstream>
#include <typeindex>
#include <map>
#include <functional>

struct GameObject;

void collide(GameObject& first, GameObject& second);

struct GameObject
{
    virtual std::type_index type() const = 0;

    virtual void collide(GameObject& other)
    {
        ::collide(*this, other);
    }
};

template <class T>
struct GameObjectImpl : public GameObject
{
    std::type_index type() const override
    {
        return typeid(T);
    }
};

struct Planet : public GameObjectImpl<Planet>
{
};

struct Asteroid : public GameObjectImpl<Asteroid>
{
};

struct Spaceship : public GameObjectImpl<Spaceship>
{
};

void spaceship_planet()   { std::cout << "spaceship lands on a planet\n";          }
void asteroid_planet()    { std::cout << "asteroid burns up in the atmosphere\n";  }
void asteroid_spaceship() { std::cout << "asteroid hits and destroys spaceship\n"; }

const std::map<std::pair<std::type_index, std::type_index>, std::function<void()>> outcomes
{
    { { typeid(Spaceship), typeid(Planet) },    spaceship_planet   },
    { { typeid(Asteroid),  typeid(Planet) },    asteroid_planet    },
    { { typeid(Asteroid),  typeid(Spaceship) }, asteroid_spaceship },
};

void collide(GameObject& first, GameObject& second)
{
    auto it = outcomes.find( { first.type(), second.type() } );

    if( it == outcomes.end() )
    {
        it = outcomes.find( { second.type(), first.type() } );

        if(it == outcomes.end() )
        {
            std::cout << "Objects pass each other harmlessly\n";
            return;
        }
    }

    it->second();
}

int main()
{
    Asteroid  asteroid;
    Planet    planet;
    Spaceship spaceship;

    collide(planet,    spaceship);
    collide(planet,    asteroid);
    collide(spaceship, asteroid);
    collide(planet,    planet);

    return 0;
}
