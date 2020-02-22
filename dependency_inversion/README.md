# Dependency Inversion
The dependency inversion principle states that:
* High-level modules should not depend on low-level modules. Both should depend on abstractions.
* Abstractions should not depend on details. Details should depend on abstractions.

When we talk about `abstractions`, we are talking about interfaces or base classes.
In the example included in this subproject, a class called `Relationships` stores the info on the
different relationships between a set of people. The `Research` class allows to query these relationships
to extract meaningful info. This `Research` class is a high-level module, while the `Relationships` one
can be considered a low-level one. When implemented the `Research` class, one may be tempted to take
the `Relationships` class directly in the constructor and loop through its internal containers
to get the info we want. However, this approach would break as soon as the implementation of the
`Relationships` class changes. This is an example of a high-level module depending on the internal low-level
module.
To fix this, the `Research` class should only interact with an abstract interface `RelationshipsBrowser`
implemented by the `Relationships` class.
