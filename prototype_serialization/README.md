# Prototype via Serialization
One of the main pain points of the whole prototype pattern is that you have to write code to make the
actual copy of the object - be it copy constructors, assignment operators or factory classes/methods.
A way to avoid this is to serialize the object, so it can be later deserialized into another copy.
There's no silver bullet, though, and additional code has to be written to handle the (de)serialization.
The sample code included in this subproject makes use of boost::serialization to serialize classes
using a human-readable scheme.
