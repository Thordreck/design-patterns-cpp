#include <string>
#include <iostream>

struct Creature
{
    std::string name;
    int attack;
    int defense;

    Creature(const std::string& name, int attack, int defense)
        : name    { name }
        , attack  { attack }
        , defense { defense }
    {}

    friend std::ostream& operator<<(std::ostream& oss, const Creature& creature)
    {
        oss << "Name: "     << creature.name
            << " attack: "  << creature.attack
            << " defense: " << creature.defense;

        return oss;
    }
};

class CreatureModifier
{
    public:
        CreatureModifier(Creature& creature)
            : creature { creature }
        {}

        void add(CreatureModifier* cm)
        {
            if(next)
            {
                next->add(cm);
            }
            else
            {
                next = cm;
            }
        }

        virtual void handle()
        {
            if(next)
            {
                next->handle();
            }
        }

    protected:
        Creature& creature;

    private:
        CreatureModifier* next { nullptr };
};

class DoubleAttackModifier : public CreatureModifier
{
    public:
        using CreatureModifier::CreatureModifier;

        void handle() override
        {
            creature.attack *= 2;
            CreatureModifier::handle();
        }
};

class IncreaseDefenseModifier : public CreatureModifier
{
    public:
        using CreatureModifier::CreatureModifier;

        void handle() override
        {
            if(creature.attack <= 2)
            {
                creature.defense++;
            }

            CreatureModifier::handle();
        }
};

class NoBonusesModifier : public CreatureModifier
{
    public:
        using CreatureModifier::CreatureModifier;

        // This is a way to stop the chain of responsibility
        void handle() override
        {
        }
};

int main()
{
    Creature goblin("Globin", 1, 1);

    CreatureModifier root      { goblin };
    DoubleAttackModifier r1    { goblin };
    DoubleAttackModifier r2    { goblin };
    IncreaseDefenseModifier d1 { goblin };

    root.add(&r1);
    root.add(&r2);
    root.add(&d1);

    root.handle();

    std::cout << goblin << std::endl;

    return 0;
}
