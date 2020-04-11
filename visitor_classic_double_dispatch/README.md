# Classic Visitor (double dispatch)
This sample code shows the traditional double dispatch visitor implementation. It provides a mechanism
to expand the functionality of entire hierarchy of classes while being as less intrusive as possible.
Basically the idea is for visitors to implement an interface with functions that accepts pointers to
each child class in the hierarchy. The base class in the hierarchy forces its children to implement
a method tipically called `accept` that takes a pointer to said interface. This `accept` method is
always implemented in the same way, the class calls the `visit` method of the visitor class passing
a pointer to itself. This allows to call the correct overload without the need for `dynamic_cast`.
While it's kind of intrusive in the sense of having to overload an `accept` method in each child class,
it allow us to add any functionality to the whole hierarchy without modifying it anymore. 
