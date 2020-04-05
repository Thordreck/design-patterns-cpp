# State: handmade implementation
A simpler and more modern approach to implement a state machine is to simply use enum classes to model
the states and the triggers. The transitions from one state to another and the event that triggers
that specific transition can be simply thought as a map of rules. After this map is populated is easy
to orchestrate the state machine by querying the container.
