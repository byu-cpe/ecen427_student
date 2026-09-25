# Iterator Invalidation

## Bug
Erasing from a container while looping over it. A range-based `for` loop uses an iterator behind the scenes; erasing the current element frees the list node that hidden iterator points to, and the loop's next step reads the freed node.

The same bug written with an explicit iterator is shown in a comment in `main.cpp`, along with the fix.

The spot to look at is marked `// HERE` in `main.cpp`.

## Common Scenario
Looping through a list to find and remove elements that match a condition (inactive, dead, off-screen), and removing them from inside the loop.

## Valgrind Output
Without valgrind this program segfaults. Under valgrind it never finishes: the first error is the real one, and everything after it is the loop wandering through garbage. Stop it with Ctrl-C.

```
Invalid read of size 8
   at 0x109847: std::_List_iterator<Item*>::operator++() (stl_list.h:289)
   by 0x10968B: ItemList::removeInactive() (main.cpp:21)
   by 0x109314: main (main.cpp:62)
 Address 0x4e20180 is 0 bytes inside a block of size 24 free'd
   at 0x484A61D: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   ...
   by 0x10967F: ItemList::removeInactive() (main.cpp:25)
   by 0x109314: main (main.cpp:62)
 Block was alloc'd at
   at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   ...
   by 0x10954C: ItemList::addItem(int, bool) (main.cpp:18)
   by 0x1092DC: main (main.cpp:59)

Use of uninitialised value of size 8
   at 0x10960B: ItemList::removeInactive() (main.cpp:22)
   by 0x109314: main (main.cpp:62)

Conditional jump or move depends on uninitialised value(s)
   at 0x10965E: ItemList::removeInactive() (main.cpp:24)
   by 0x109314: main (main.cpp:62)

Invalid free() / delete / delete[] / realloc()
   at 0x484A61D: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x10966C: ItemList::removeInactive() (main.cpp:24)
   by 0x109314: main (main.cpp:62)
 Address 0x1ffefff5d8 is on thread 1's stack

... and so on, forever.
```

Read the first error and ignore the rest. Its stack trace is full of `std::list` internals, which is typical for this bug; skip past the library frames to the first line in your own code. The invalid read is at `main.cpp:21` (the `for` line, where the hidden iterator advances), and the memory was freed at `main.cpp:25` (the `remove`). Once the loop has followed a dangling pointer, every later access is to garbage, and valgrind reports each one: uninitialised values, a `delete` of a stack address, and eventually the loop simply never reaches `end()`.

## Key Lesson
Never erase from a container inside a range-based `for` loop over it. Use an explicit iterator instead: `erase()` returns an iterator to the next element, so write `it = items.erase(it);` and skip the `++it` on that path. Other safe options are `std::remove_if` followed by `erase`, or collecting the items to remove and erasing them after the loop. This applies to `std::vector` too, where erasing invalidates every iterator past the erased element.
