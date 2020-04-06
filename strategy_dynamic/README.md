# Dynamic Strategy
The strategy design patterns aims to split a class from certain aspect of its behavior. This can be achieved
either on runtime or on compile time (this is usually refered to as policies).
In this example the class `TextProcessor` holds a reference to a strategy class that defines
how a list should be printed. The strategy objects implement a specific interface to construct a list
using either html or markdown formats.
