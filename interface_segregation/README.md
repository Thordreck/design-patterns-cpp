# Interface Segregation
Snippet code showcasing the concept of `Interface Segregation`.
This principle basically boils down to "do not put too much stuff in an interface". Stuffing up way too many
methods in a single interface may force users to implement methods they are not interested in,
or that do not even make sense in a given context.

For example, in the snippet included in this subfolder, a virtual interface called `IMachine` models
a device capable of printing, scanning and sending faxes. Users implementing a simple scanner have
to override not only the `scan()` function they are interested on, but also the `fax()` and `print()` functions.
Even if they left the methods empty or threw a `NotValidOperation` exception, end-users using this
API still get the wrong message. That is, that a `Scanner` class do have a `fax()` and `print()` methods.
