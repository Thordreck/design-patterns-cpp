# Composite
The composite design pattern represents the idea of treating both individual objects and groups in a uniform
manner. This is enforced by sharing a common interface. In the sample code included in this subproject,
both the classes `Circle` and `Group` inherits from `GraphicObjects`. Internally, the `Group` class
stores a collection of `GraphicObjects`, and calls recursively its objects interface methods when
their own functions are called (the `draw()` function in this case).
