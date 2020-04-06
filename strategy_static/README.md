# Static Strategy
This example shows the use of static strategies (also called policies, more so in the C++ community).
Instead of setting the strategy on runtime, it's passed to the class a template argument.
This is just a personal opinion, but I feel the original video and example do not make policies justice at
all. The example keeps the virtual interface and the inheritance. Programmers reading this for the first
time may wonder what's the point of using the static approach. In the static approach inheritance is not needed.
You can put whatever in the template as long as the resulting code is correct.
