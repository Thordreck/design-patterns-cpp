# Array-backed Properties
Sometimes it's useful to perform operations on several properties in a class - for example,
to compute the average, find the maximum value, etc. Defining all the class' properties
as individual members do not scale well, as we would have to change all the code everytime
we add a new field.
Instead of that, it's sometimes useful to pack all members in a single container (for example
a std::array). We can use a single private enum as indexes to the array, to help writing any
getter or setters. But now, these composite operations become way simpler. From the point of view
of the user nothing has changed, as he still has access to individual members.
