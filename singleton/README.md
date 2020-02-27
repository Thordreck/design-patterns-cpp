# Singleton
Singletons are objects that are only instatiated once, and only that single object exists during the lifetime
of the programs. Tipically, users get a reference to this instatiated object using some kind of static method.
The constructor of the class is kept private, and both the copy constructor and assignment operator are
disabled.
Singletons may come in handy when they model a resource that's either expensive to initialize, or that
it makes sense to only have one, as it may be the case with a database. Singletons remain one of the most
controversials design patterns.
