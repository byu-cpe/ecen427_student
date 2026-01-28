# Uninitialized Memory - Using Variables Before Initialization

## Bug Type
Reading from a variable (especially class members) that was never assigned a value. The variable contains garbage data.

## Common Scenario
A class has member variables that are not initialized in the constructor's initializer list or body. Later, the code reads these members assuming they have valid values (e.g., checking a counter or using a pointer).

## Valgrind Output
```
Conditional jump or move depends on uninitialised value(s)
  at 0x...: function_name (file.cpp:line)
```

or

```
Use of uninitialised value of size X
```

## How to Expose the Bug

To see the uninitialized memory bug in action, uncomment the code at the beginning of `main()` that creates a garbage-filled buffer. This pollutes the stack with non-zero values (0xAA), causing `tickCount` to be initialized with garbage data. This makes the bug obvious - the counter will trigger immediately instead of after 10 ticks.

## Key Lesson
Always initialize all member variables in the constructor initializer list. In C++11+, you can also use in-class member initializers (e.g., `int count = 0;` in the class definition).
