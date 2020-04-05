# Memento: Undo and Redo
Similar to the command design pattern, mementos give us the possibility to undo and redo previous
operations, by rolling back to the state previous to each operation. In this example, the bank account class
keeps a history of the mementos created by each operation, and exposes a `undo` and `redo` methods to
navigate through said history.
