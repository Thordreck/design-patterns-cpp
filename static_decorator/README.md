# Static Decorator
A static decorator implementation makes use of templates, and inheritance to this same
template parameter, to expan on the original class' functionalities. Contrary to the
dynamic implementation, it's possible to access the original API defined by the class, since we
are using inheritance instead of aggregation.
Also, it's possible to pass all the arguments of the template chain in the same constructor,
by forwarding the arguments to the parent's constructor.
