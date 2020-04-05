# Observer: The problem of dependencies
A problem arises with the observer design pattern when we introduce parameters that are dependent to others.
This example introduces the method `Person::can_vote()`, which depends on the age of the person object.
Introducing notifications on this parameters usually involves adding additional code in the other
parameter to handle these new notifications. As more dependent parameters are introduced, this approach
can become hardly usable. One may consider building additional infrastructure to handle the dependency
traversal and notification logic.
