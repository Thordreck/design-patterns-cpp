# Singleton via Dependency Injection Framework
Not a design pattern per se, but it's worth noting that a `Singleton` is just an object with a special
lifetime cycle (only an instance through all the program). As such, it's possible to delegate the lifetime
management to a specialized framework that takes care of its lifetime. In this example the framework used its lifetime. In this example the framework used is
boost::DI.
