# Pointer Chain of Responsibility
A chain of responsibility describes a succession of entities that could potentially handle a specific
event or request. Take for example a button click in a GUI program. This "clicked" event could be handle
by the button itself. Or the button could defer this task to the element preceding it (for example
the form it's embedded into). This preceding element could also refer the responsibility to the underlying
window, and so on and so forth.
This example shows how chain of responsibilities were traditionally implemented. The idea was to create an
external class that takes a reference to an object or event we want to handle. Internally, this class
keeps a single-linked list with all the elements in the chain. To implement a new element in the chain, one
would have to inherit from the base handler, and implement the `handle` function. It's important to not forget
to call the base class `handle` method, as it's the one in charge of propagating the event.
