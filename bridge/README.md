# Bridge
The bridge design pattern is conceived to avoid a so called "cartesian product" explosion of classes and
dependencies. Imagine the following scenario: we are working in a program to display different shapes
on screen. There are two ways to render each shape - namely, rasterized or vectorized. If we suppose there
are three shapes (circle, square and triangle), we may end up with an explosion of classes of type
`RasterCircle`, `VectorCircle`, `RasterSquare`, `VectorSquare` and so on.
The idea of a bridge is to split the class hierarchy into two different hierarchy trees. One for the
render mode and another one for the shapes themselves. Internally, the `Shape` class holds a reference
to a `Render` base class. Each `Render` child class implements how it draws each shape. When a shape
it's called to draw itself, it calls the function exposed by the renderer to draw that specific shape.
Notice how adding more types of render do not affect the shape hierarchy tree, since renderers are injected
through the `Shape` constructor.
