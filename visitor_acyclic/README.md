# Acyclic Visitor
The acyclic visitor implementation uses templates and inheritance to provide further flexibility
to the visitors. In this approach the visitor class do not have to implement the function
for each child class. Instead it can choose what classes it wants to accept and process, and the rest
of them would be a no-op.
