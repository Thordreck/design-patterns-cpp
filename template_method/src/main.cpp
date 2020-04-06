#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

class Game
{
    public:
        Game(int number_of_players) : number_of_players(number_of_players) {}
        virtual ~Game() = default;

        void run()
        {
            start();
            while(!have_winner())
            {
                take_turn();
            }

            std::cout << "Player " << get_winner() << " wins.\n";
        }

    protected:
        virtual void start()       = 0;
        virtual bool have_winner() = 0;
        virtual void take_turn()   = 0;
        virtual int  get_winner()  = 0;

    protected:
        int number_of_players;
        int current_player { 0 };
};

class Chess : public Game
{
    public:
        Chess() : Game(2) {}

    protected:
        void start() override
        {
            std::cout << "Starting a game of chess with "
                      << number_of_players << "players\n";
        }

        bool have_winner() override
        {
            return turn == max_turns;
        }

        void take_turn() override
        {
            std::cout << "Turn " << turn << " taken by "
                      << current_player  << "\n";

            turn++;

            current_player = (current_player + 1) % number_of_players;
        }

        int get_winner() override
        {
            return current_player;
        }

    private:
        int turn { 0 };
        const int max_turns { 10 };
};

int main()
{
    Chess chess;
    chess.run();

    return 0;
}
