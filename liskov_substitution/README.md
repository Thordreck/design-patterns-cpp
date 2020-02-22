# Specification Pattern
Snippet code showcasing the concept of `Liskov substitution`.
This principle states that any function that operates with a base class should work as expected
if said base class is substituted by any of its inherited classes.

The code in this example does not satisfy this condition. The function `process` does not work
as expected when used with objects of the `Square` class, even though it inherits from the `Rectangle` class.
