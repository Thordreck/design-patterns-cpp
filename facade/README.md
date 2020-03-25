# Façade
The façade design pattern is all about hiding complexity away from users. It consists on encapsulating
initialization code, boilerplate code or simply complex sequences of operations into a simpler and more
user-friendly class or function.
The example included in this subproject makes use of the example project called `bloom`
provided by the author. The Console class defined encapsulates the initialization of an OpenGL
multicolum window into a simpler self-contained class. Take a look at the file
located at 3rdparty/bloom/src/Bloom.cpp to see how the same code would look like without the façade.
Also note that, to compile `bloom` you will need to have installed the following dependencies:

* Boost
* OpenGL
* GLFW 3
* Glew
* Freetype
