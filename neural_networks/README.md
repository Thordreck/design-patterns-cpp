# Neural Networks
Neural networks can be seen as a type of composite design. This example showcases how to
implement a connection mechanism between single neurons and layers of several of them.
It makes use of the Curiously Recurring Template Pattern (CRTP) to implement a generic
connect function, that iterates through all the input and output neurons and connect them.
The trickiest part is to make a single neuron to act as an iterable of a single entry, by
implementing a begin() and end() methods.
Without this approach, we would have at least four different connection scenarios - that is,
from neuron to neuron, from neuron to layer, from layer to neuron and from layer to layer.
