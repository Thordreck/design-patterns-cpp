#include <string>
#include <iostream>

#include <boost/signals2.hpp>

using namespace boost::signals2;

struct EventData
{
    virtual ~EventData() = default;
    virtual void print() const = 0;
};

struct PlayerScoredData : public EventData
{
    std::string player_name;
    int goals_scored_so_far;

    PlayerScoredData(const std::string& player_name, int goals_scored_so_far)
        : player_name         (player_name)
        , goals_scored_so_far (goals_scored_so_far)
    {}

    void print() const override
    {
        std::cout << player_name << " has scored! "
                  << "(their "   << goals_scored_so_far
                  << " goal)\n";
    }
};

// This is the mediator
struct Game
{
    signal<void(EventData*)> events;
};

struct Player
{
    std::string name;
    int goals_scored { 0 };
    Game& game;

    Player(const std::string& name, Game& game)
        : name (name)
        , game (game)
    {}

    void score()
    {
        goals_scored++;
        PlayerScoredData data { name, goals_scored };
        game.events(&data);
    }
};

struct Coach
{
    Game& game;

    Coach(Game& game) : game(game)
    {
        game.events.connect([] (EventData* event)
            {
                auto* ps = dynamic_cast<PlayerScoredData*>(event);

                if(ps != nullptr && ps->goals_scored_so_far < 3)
                {
                    std::cout << "coach says: well done " << ps->player_name << "!\n";
                }
            });
    }
};

int main()
{
    Game game;
    Player player { "sam", game };
    Coach coach { game };

    player.score();
    player.score();
    player.score();

    return 0;
}
