# Monostate
The `Monostate` design pattern is an approach to implement the `Singleton` pattern. Instead of ensuring
that only one instance of a specific class exists at any given time, a monostate class implements
all its storage as static. Every single instance of said class would operate over the same storage.
This pattern should be avoided if possible. Static storage does not play well with inheritance. Also,
users do not get informed in a straightforward way that special lifetime rules apply to the class
they are interacting with, and that unexpected results may appear.
