# Factory Class
Factory classes are similar to their methods counterparts. The only difference is that the factory methods
are encapsulated in an external entity (a class). There's a downside to this approach, though. Taking out
the factory methods to a class means that now this factory should have access to the private constructor
to be able to actually instantiate the class. However, going back to the original class to declare the
factory a friend class breaks the `Open-Close principle`. Another solution would be to make the class
constructor public. Pick your poison.

