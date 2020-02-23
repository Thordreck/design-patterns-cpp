# Simple Builder
The builder design pattern is used when instantiating a fullly functional object in one single step would
be too difficult or cumbersome. Instead of having a huge constructor with all the pieces needed,
the creation is done piecewise using an external builder class.
In the snippet included in this subproject, a dedicated class (`HtmlBuilder`) is used to let users
build an html document step by step by adding the tags (`HtmlElement` class). Not having a builder would
mean that all the tags had to be provided when the `HtmlElement` is instantiated.
