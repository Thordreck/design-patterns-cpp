# Template Method
The template method design pattern is similar to the strategy pattern, in that both splits functionality
in high and low-level behavior. However, in the template method approach, the low-level functionality
is not separated in its own entity. Specific algorithms or behavior inherit from the general one
and fill in the gaps to make the whole functional (aka, they implement virtual methods missing
in the general case).
