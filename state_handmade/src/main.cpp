#include <iostream>
#include <vector>
#include <map>

enum class State
{
    off_hook,
    connecting,
    connected,
    on_hold,
    on_hook
};

inline std::ostream& operator<<(std::ostream& oss, const State& state)
{
    switch(state)
    {
        case State::off_hook:
            oss << "off the hook";
            break;
        case State::connecting:
            oss << "connecting";
            break;
        case State::connected:
            oss << "connected";
            break;
        case State::on_hold:
            oss << "on hold";
            break;
        case State::on_hook:
            oss << "on the hook";
            break;
    }

    return oss;
}

enum class Trigger
{
    call_dialed,
    hung_up,
    call_connected,
    placed_on_hold,
    taken_off_hold,
    left_message,
    stop_using_phone
};

inline std::ostream& operator<<(std::ostream& oss, const Trigger& trigger)
{
    switch(trigger)
    {
        case Trigger::call_dialed:
            oss << "call dialed";
            break;
        case Trigger::hung_up:
            oss << "hung up";
            break;
        case Trigger::call_connected:
            oss << "call connected";
            break;
        case Trigger::placed_on_hold:
            oss << "placed on hold";
            break;
        case Trigger::taken_off_hold:
            oss << "taken off hold";
            break;
        case Trigger::left_message:
            oss << "left_message";
            break;
        case Trigger::stop_using_phone:
            oss << "putting phone on hook";
            break;
    }

    return oss;
}

int main()
{
    std::map<State, std::vector<std::pair<Trigger, State>>> rules;

    rules[State::off_hook] = {
        { Trigger::call_dialed,      State::connecting },
        { Trigger::stop_using_phone, State::on_hook    },
    };

    rules[State::connecting] = {
        { Trigger::hung_up,        State::off_hook  },
        { Trigger::call_connected, State::connected },
    };

    rules[State::connected] = {
        { Trigger::left_message,   State::off_hook  },
        { Trigger::hung_up,        State::off_hook  },
        { Trigger::placed_on_hold, State::on_hold   },
    };

    rules[State::on_hold] = {
        { Trigger::taken_off_hold, State::connected  },
        { Trigger::hung_up,        State::off_hook   },
    };

    const State entry_state   { State::off_hook };
    const State exit_state    { State::on_hook  };

    State current_state { entry_state };

    while(current_state != exit_state)
    {
        std::cout << "The phone is currently " << current_state << std::endl;

        std::cout << "Select a trigger:\n";

        size_t idx { 0 };

        for(auto item : rules[current_state])
        {
            std::cout << "\t" << idx++ << ". " << item.first << std::endl;
        }

        size_t input;
        std::cin >> input;

        if(input < 0 || input + 1 > rules[current_state].size())
        {
            std::cout << "Incorrect option. Please, try again..." << std::endl;
        }

        current_state = rules[current_state][input].second;
    }

    std::cout << "We are done using the phone\n";

    return 0;
}
