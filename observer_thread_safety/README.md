# Observer: Thread safety and reentrancy
Depending on how the observer logic is written, we may run into issues with thread-safety. The usual
approach to fix this is to add mutexes to guard the vector of observers. This simply fix could
also potentially bring reentrancy issues. For example, if an observer tries to unsubscribe in its own
notification method. Structures such as std::recursive_mutex may fix this, even though they are not 
too popular as a solution.
