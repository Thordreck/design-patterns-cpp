# Reflective Visitor
The visitor implementation shown in this example is a step ahead from the first "instrusive visitor" approach.
The old `print` method that had to be implemented in each `Expression` subclass is now removed, and a new
class that handles the printing is introduced (we are thus keeping the single responsibility principle).
Now the problem we run in static typed languages such as C++, is that we don't know to what child a pointer
to a base class refers to (to print its contents correctly). The naïve approach taken in this
example makes use of `dynamic_cast` to check every single possible child class and print its contents
correctly.
This is obviosly not the prefered solution, as every single time we add a new child class we cannot forget
to add a new branch.
