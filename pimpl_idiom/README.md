# PIMPL Idiom
The PIMPL Idiom is a pattern where the internal details and implementation of a class are separated from their
interface. Public methods are declared in the header file as usual, as well as a pointer or reference to a
pimpl class. This class is fully defined in the cpp associated to the original class. The original methods
delegate their actual work to other methods in the pimpl class.
This idiom brings several advantages. First, the internal workings of the class are hidden in the source file,
that does not have to be shipped to the end user. Users only see a reference to a pimpl class, public methods
and some variable members if any. Also, it's possible on compilation time to decide which pimpl will be compiled
alongside the public header. This is useful to support different architectures (ex, Windows vs Linux).
Finally, while less and less relevant nowadays, the pimpl idiom reduces compilation time, as changes in the
internal implementation do not affect the public header.
