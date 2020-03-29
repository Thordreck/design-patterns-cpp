#include <string>
#include <iostream>

#include <boost/signals2.hpp>

using namespace boost::signals2;

struct Query
{
    std::string creature_name;

    enum Argument
    {
        attack,
        defense
    } argument;

    int result;
};

// This is a mediator
struct Game
{
    signal<void(Query&)> queries;
};

struct Creature
{
    Game& game;

    std::string name;

    int attack;
    int defense;

    int get_attack() const
    {
        Query q { name, Query::Argument::attack, attack };

        game.queries(q);

        return q.result;
    }

    friend std::ostream& operator<<(std::ostream& oss, const Creature& creature)
    {
        oss << "Name: "     << creature.name
            << " atttack: " << creature.get_attack();

        return oss;
    }
};

class CreatureModifier
{
    public:
        CreatureModifier(Game& game, Creature& creature)
            : game     { game }
            , creature { creature }
        {}

    private:
        Game& game;
        Creature& creature;
};

class DoubleAttackModifier : public CreatureModifier
{
    public:
        DoubleAttackModifier(Game& game, Creature& creature)
            : CreatureModifier(game, creature)
        {
            conn = game.queries.connect([&] (Query& q)
                    {
                        if(q.creature_name == creature.name &&
                           q.argument == Query::Argument::attack)
                        {
                            q.result *= 2;
                        }
                    });
        }

        ~DoubleAttackModifier()
        {
            conn.disconnect();
        }

    private:
        connection conn;
};

int main()
{
    Game game;
    Creature goblin { game, "Strong Goblin", 2, 2 };

    std::cout << goblin << std::endl;

    {
        DoubleAttackModifier dam { game, goblin };
        std::cout << goblin << std::endl;
    }

    std::cout << goblin << std::endl;

    return 0;
}
