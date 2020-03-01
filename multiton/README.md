# Multiton
A `Multiton` can be seen as an entity that encapsulates several singletons that are related to each other.
Users can query the multiton using some sort of key and, for a given key, a reference to the same instance
will be returned. In this example, the `Multiton` class has a simple static std::map that holds references
to the different singletons. The key was implemented as an enum class with three entries defined.
