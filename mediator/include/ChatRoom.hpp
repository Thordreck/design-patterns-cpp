#ifndef CHAT_ROOM_HPP
#define CHAT_ROOM_HPP

#include <vector>

struct Person;

struct ChatRoom
{
    std::vector<Person*> people;

    void broadcast(const std::string& origin,
                   const std::string& message);

    void join(Person* person);

    void message(const std::string& origin,
                 const std::string& who,
                 const std::string& message);
};

#endif
