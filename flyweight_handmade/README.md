# Handmade flyweight
The flyweight design patterns aims to reduce the memory footprint of a program. It does so by
sharing values that are equal across several objects. In the example included in this subproject,
a really simple flyweight implementation is shown. The idea is to only have one instance
of the same string, that it's shared between several `User` objects.
