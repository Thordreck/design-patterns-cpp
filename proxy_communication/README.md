# Communication Proxy
This example showcases another use of the proxy design pattern. This time, the proxy is used
to masks a command that's executed in a remote server using a previously-defined interface
( the `Pingable` interface). From the end-user's point of view the interface remains the same, even
though the command is being executed remotely.
Note that this example connects to a remote online server, so an internet connection is required.
