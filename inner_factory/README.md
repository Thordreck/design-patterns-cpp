# Inner Factory
The Inner Factory pattern differs a bit from the Factory Class pattern. In this approach, the factory class
is defined inside the target class. This removes the need to befriend the factory, with the downside that
the factory should be designed and implemented at the same time as the class itself.
This pattern is usually used to give more hints to the end-user as to how the class should be instantiated.
In this particular example, a `Point` object can be created as follows:
```
auto p = Point::Factory.NewPolar(5, M_PI_4);
```
