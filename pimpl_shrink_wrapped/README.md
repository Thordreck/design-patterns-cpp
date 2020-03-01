# Shrink-wrapped PIMPL
This sample code includes a small header-only class that encapsulates a general pimpl. It manages the creation
and destruction of the impl class (using std::unique_ptr), and exposes both the `*` and `->` operator.
