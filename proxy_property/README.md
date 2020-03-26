# Property Proxy
A proxy is an entity that wraps another one, and acts as it was the original one, but adding
additional functionality. For example, smart pointers follow the proxy design pattern, as they add
automatic reference counting and deallocation on top of the API defined by the object they contain.
This subproject showcases the use of yet another type of proxy - the property proxy. It wraps a member
in a struct or class and provides automatic setters and getters than we can modify to add checks or
whatever code we may need to run.
