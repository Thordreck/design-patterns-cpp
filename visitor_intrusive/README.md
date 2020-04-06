# Intrusive Visitor
The visitor design pattern allows us to traverse a class hierarchy to perform some kind of
operation of fetch some info. This example shows the naive approach to implement such design. That is,
by going back to the hierarchy and modify it to add the kind of function we need (in this particular
example it's a print method). This is not the best approach, since not only breaks the open-closed
principle, but also it doesn't really scalate well.
