# Uninitialized Memory

## Bug
A member variable (`count`) is never given an initial value, so it starts with whatever garbage happened to be in memory.

The spot to look at is marked `// HERE` in `main.cpp`.

## Common Scenario
A constructor that initializes some members but forgets one. Members are *not* automatically zeroed in C++.

## Valgrind Output
Run with `--track-origins=yes` (the Makefile does this) so valgrind reports where the uninitialized value came from:

```
Conditional jump or move depends on uninitialised value(s)
   at 0x10927A: Counter::tick() (main.cpp:10)
   by 0x1091C9: main (main.cpp:25)
 Uninitialised value was created by a stack allocation
   at 0x109189: main (main.cpp:22)

Counter expired on tick 9
Counter expired on tick 19
Counter expired on tick 29

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 10 errors from 1 contexts (suppressed: 0 from 0)
```

Under valgrind the output looks correct (ticks 9, 19, 29), because valgrind happened to leave a zero in the stack slot holding `count`. Run the same program natively (`make run`) and you may see something else entirely:

```
Counter expired on tick 0
Counter expired on tick 10
Counter expired on tick 20
```

Here the slot held leftover garbage of 9 or more, so the very first `tick()` tripped the counter. That is what makes uninitialized memory so nasty: the behavior depends on whatever was in memory before, so it can change from run to run, machine to machine, or after an unrelated edit elsewhere in the program. Valgrind reports the error regardless of what value was there.

## Key Lesson
Initialize every member variable in the constructor initializer list, or with an in-class initializer (`int count = 0;`). Bugs from uninitialized memory are unpredictable and hard to reproduce, so valgrind is often the only reliable way to find them.
