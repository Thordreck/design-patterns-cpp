# State: classic implementation
The state design pattern is basically a finite state machine implementation. This example shows the classic
approach to implement FSM using C++ that are usually found in literature. It's based on state classes
sharing a base class, and a mediator that handle the state changes by leveraging it into the state derived
classes.
This approach is not the recommended one nowadays, but it's included for completion's sake.
