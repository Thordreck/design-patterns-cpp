# Virtual Proxy
A virtual proxy is a way to mock an already existing class but changing its behavior in some way.
In this example, the class `LazyBipmap` implements the same inteface as the normal `Bitmap` class,
but it defers the loading of the file until its `draw()` function is actually called for the first time.
The only code change needed is to change the class type at the beginning.
