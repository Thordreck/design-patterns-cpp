# Factory Methods
In general, factories are entities whose only task is to provide an API to instantiate objects of a given
class. Factories are interesting to use when:
* The construction process of a class has become too convoluted, due to a high number of settings and options.
 Trying to fit everything in a single constructor would require lots of options parameters and flags.
* You would like to add another constructor with a different conceptual meaning, but there's already another
 one with the same signature. Delegating the construction to external entities allows to have more clear
 and explicit signatures (as opposed to constructors, where the name has to match that of the class).

This particular example focuses on `Factory Methods`. The `Point` class in the sample code does not
expose any constructor. Instead, it implements several static public methods that constructs and initialize
the object and returns it. This allows to have a more expressful API (`Point::NewCartesian` and `Point::NewPolar`).
