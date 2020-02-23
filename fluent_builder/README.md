# Fluent Builder
This examples introduces several improvements over the simple builder pattern.
* `HtmlElement` constructors are now private, and `HtmlBuilder` is a friend class. This enforces users to user the builder instead of interacting with the elements directly.
* `add_child()` method now returns a reference to the builder itself, thus allowing end-users to chain together calls. This is known as a `fluent builder`.
