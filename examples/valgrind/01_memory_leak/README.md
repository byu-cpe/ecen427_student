# Memory Leak

## Bug
An object created with `new` is never deleted. `ItemManager::removeItem()` erases the pointer from the list but forgets to `delete` the `Item` it points to. Nothing else references the object anymore, so the memory can never be freed. The destructor of `ItemManager` deletes whatever is still in the list, which is why items 1 and 3 are destroyed and item 2 is not.

The spot to look at is marked `// HERE` in `main.cpp`.

## Common Scenario
Removing an object from a container and forgetting that removing the *pointer* does not free the *object*. The same "definitely lost" report appears when a class that owns objects has no destructor at all.

## Valgrind Output
This example's Makefile builds without debug info. Valgrind still finds the leak, but it can only tell you which function it was in:

```
4 bytes in 1 blocks are definitely lost in loss record 1 of 1
   at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x1094B6: ItemManager::addItem(int) (in /home/user/examples/valgrind/01_memory_leak/memory_leak)
   by 0x1092B2: main (in /home/user/examples/valgrind/01_memory_leak/memory_leak)

LEAK SUMMARY:
   definitely lost: 4 bytes in 1 blocks
   indirectly lost: 0 bytes in 0 blocks
     possibly lost: 0 bytes in 0 blocks
   still reachable: 0 bytes in 0 blocks
        suppressed: 0 bytes in 0 blocks

ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

Add `-g` to `CXXFLAGS` in the Makefile, rebuild (`make clean; make valgrind`), and valgrind reports file names and line numbers:

```
4 bytes in 1 blocks are definitely lost in loss record 1 of 1
   at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x1094B6: ItemManager::addItem(int) (main.cpp:18)
   by 0x1092B2: main (main.cpp:46)
```

Note that the stack trace shows where the leaked memory was *allocated* (line 18, in `addItem()`), not where you forgot to delete it (`removeItem()`). Valgrind can't know where the delete should have been; that part is up to you.

## Key Lesson
Every `new` needs exactly one matching `delete`. Always build with `-g` before running valgrind, or you will get function names without line numbers.
