# Prototype
The prototype design patterns consists on creating another object by taking another existing copy of the
object as the basis, rather than starting from scratch. This can be convenient when, for example,
two objects are nearly identical and differ only in some members. After copying the other object users
can apply whatever changes may be needed.
The simplest way to implement this (and the way it's used in this sample code) is by implementing
a copy constructor. Special care should be taken when the class have references or pointers. Using
the default copy constructor would not work as expected, as it only does a shallow copy
(pointers themselves are copied, thus the two objects would point to the same memory). To fix this,
a explicit copy constructor that dereference the pointer and copy their contents (deep copy)
has to be implemented.
