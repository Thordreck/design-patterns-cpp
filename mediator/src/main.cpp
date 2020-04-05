#include "Person.hpp"
#include "ChatRoom.hpp"

int main()
{
    ChatRoom room;

    Person john { "John" };
    Person jane { "Jane" };

    room.join(&john);
    room.join(&jane);

    john.say("hi room");
    jane.say("oh, hey John");

    Person simon { "Simon" };
    room.join(&simon);
    simon.say("Hi everyone!");

    jane.pm("Simon", "glad you found us, Simon!");

    return 0;
}
