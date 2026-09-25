# Missing Destructor

## Bug
`Container` creates five `Block` objects with `new` and stores the pointers in a vector, but it has no destructor. When the `Container` is deleted, the vector of pointers is freed, but the `Block` objects the pointers referred to are not. Notice in the program output that every block is created and none is destroyed.

The spot to look at is marked `// HERE` in `main.cpp`.

## Common Scenario
A class that owns dynamically allocated objects (a level, a manager, a composite object) and never defines a destructor to free them. The compiler-generated destructor destroys the vector, not what the pointers in it point to.

## Valgrind Output
```
20 bytes in 5 blocks are definitely lost in loss record 1 of 1
   at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x109473: Container::Container() (main.cpp:19)
   by 0x1092AD: main (main.cpp:31)

LEAK SUMMARY:
   definitely lost: 20 bytes in 5 blocks
   indirectly lost: 0 bytes in 0 blocks
     possibly lost: 0 bytes in 0 blocks
   still reachable: 0 bytes in 0 blocks
        suppressed: 0 bytes in 0 blocks

ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

All five leaks share one allocation site, line 19 in the `Container` constructor, so valgrind groups them into a single loss record of 5 blocks. As always, the trace shows where the memory was allocated, not where it should have been freed.

## Key Lesson
If a class creates objects with `new`, it needs a destructor that deletes them. Follow the "Rule of Three/Five": once you write a destructor, you almost certainly need to write (or delete) the copy constructor and assignment operator too, or two containers will end up deleting the same blocks. Smart pointers (`std::unique_ptr`) avoid the whole problem.
