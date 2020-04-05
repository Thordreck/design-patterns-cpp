# Memento
A memento is a token that stores a class' state at a particular time. It can be thought as a kind of
snapshot of a class' internal state. This memento can be used to roll back to the state it contains.
In this example, a bank account class returns a `Memento` object from its 'deposit' method. This
memento can be used later in its `restore` method to roll back the balance to its previous value.
Note that mementos are usually inmutable, as it wouldn't make that much sense to be able to modify
a previous snapshot.
