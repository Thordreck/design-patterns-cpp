#include <algorithm>

#include "ChatRoom.hpp"
#include "Person.hpp"

void ChatRoom::broadcast(const std::string& origin,
                         const std::string& message)
{
    for(auto* person : people)
    {
        if(person->name != origin)
        {
            person->receive(origin, message);
        }
    }
}

void ChatRoom::join(Person* person)
{
    const auto& join_msg = person->name + " joins the chat";

    broadcast("room", join_msg);

    person->room = this;
    people.push_back(person);
}

void ChatRoom::message(const std::string& origin,
                       const std::string& who,
                       const std::string& message)
{
    auto target = std::find_if(std::begin(people), std::end(people),
                              [&] (const auto* person)
                              {
                                return person->name == who;
                              });

    if(target != std::end(people))
    {
        (*target)->receive(origin, message);
    }
}
