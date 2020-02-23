# Builder Facets
This sample code showcases the use of multiple builders to fill all the info needed by a given class (`Person`).
The specific builders all inherit from a virtual base class, that keeps a single reference to the class
being built. This way objects are not constatly copied when the different builders are created.
Each builder is fluent, thus allowing users to concatenate the calls using a more natural syntax as shown below.
```cpp
    Person p = Person::create()
        .lives().at("123 London Road")
                .with_postcode("SW1 1GB")
                .in("London")
        .works().at("PragmaSoft")
                .as_a("Consultant")
                .earning(10e6);
```
