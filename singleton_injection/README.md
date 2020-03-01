# Singleton Injection
Systems that implement singleton are usually difficult to test. Tests usually take a reference to the
singleton instance and operate on them. Depending on the nature of the resource the singleton is
pointing at, this approach may not work as expected. For example, if the singleton models a database,
said database may not be available in the dev environment.
To aovid this kind of issues, one approach is to declare the interface the singleton is going to
offer as a virtual class, and make the singleton inherit from it. Now it's possible to mock the singleton
interface with dummy data, and make the test operate on the common base virtual class.
