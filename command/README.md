# Command
Normally statements are said to be perishable. This means that any operation or assignment is
lost once it's done and no traces of it are left. The command design patterns is all about encapsulating
these perishable statements, so as to keep a log or history record of all the manipulation done
on a class or entity. This is usually the approach taken to implement commands history in Ctrl-Z commands or
in macro recordings utilities.
The example in this subproject implements a simple command implementation over a `BankAccount` class. 
