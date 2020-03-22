#include <array>
#include <iostream>
#include <algorithm>
#include <numeric>

class Creature
{
    private:
    enum Abilities
    {
        str,
        agl,
        intl,
        count
    };

    public:
    int get_strength() const { return abilities[str]; }
    void set_strength(int value) { abilities[str] = value; }
    
    int get_intelligence() const { return abilities[intl]; }
    void set_intelligence(int value) { abilities[intl] = value; }

    int get_agility() const { return abilities[agl]; }
    void set_agility(int value) { abilities[agl] = value; }

    int sum() const
    {
        return std::accumulate(abilities.begin(), abilities.end(), 0);
    }

    double average() const
    {
        return sum() / static_cast<double>(count);
    }

    int max() const
    {
        return *std::max_element(abilities.begin(), abilities.end());
    }

    private:
    std::array<int, count> abilities;
};

int main()
{
    Creature orc;
    orc.set_strength(60);
    orc.set_agility(11);
    orc.set_intelligence(3);

    std::cout << "The orc has an average stat of: "
              << orc.average()
              << " and a maximum stat of: "
              << orc.max()
              << std::endl;

    return 0;
}
