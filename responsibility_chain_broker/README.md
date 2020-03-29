# Broker Chain of Responsibility
This example puts together several design patterns to implement a more sophisticated chain of
responsibility. It makes use of boost::signals2 to handle queries that go through a mediator
(the `Game` class). Each modifier subscribes to these signals and modify the values if needed
- that is, they handle the events if needed.
The `Creature` class fires the event in its getter method, and return the value that has been
processed by each subscribed entity. This particular implementation disconnects the signal in the
modifier's destructor, thus allowing for temporal modifiers.
