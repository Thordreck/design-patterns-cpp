# Dynamic Decorator
The decorator pattern allows to extend the functionality of an already-existing class without
modifying the original source code - thus respecting the open-closed principle.
In the example included in this subproject, a dynamic decorator is implementing by inheriting
from a given base class, taking a reference to this same base class, and adding some functionality
on top of it. For example, a `ColoredShape` takes a reference to a base class `Shape`, but adds
the concept of color to it.
