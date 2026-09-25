# Iterator Invalidation

## Bug
Erasing from a container in the middle of an iterator loop, then continuing to use the old iterator. `items.erase(it)` frees the list node that `it` points to, and the loop's `++it` then reads that freed node.

## Common Scenario
Looping through a list to find and remove elements that match a condition (inactive, dead, off-screen), and calling `erase(it)` without using its return value.

## Valgrind Output
```
Invalid read of size 8
   at 0x109849: std::_List_iterator<Item*>::operator++() (stl_list.h:289)
   by 0x109679: ItemList::removeInactive() (main.cpp:21)
   by 0x1092F4: main (main.cpp:41)
 Address 0x4e20180 is 0 bytes inside a block of size 24 free'd
   at 0x484A61D: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   ...
   by 0x109940: std::__cxx11::list<Item*, std::allocator<Item*> >::erase(std::_List_const_iterator<Item*>) (list.tcc:158)
   by 0x10966D: ItemList::removeInactive() (main.cpp:25)
   by 0x1092F4: main (main.cpp:41)
 Block was alloc'd at
   at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   ...
   by 0x1098C0: std::__cxx11::list<Item*, std::allocator<Item*> >::push_back(Item*&&) (stl_list.h:1311)
   by 0x10952C: ItemList::addItem(int, bool) (main.cpp:18)
   by 0x1092BC: main (main.cpp:38)

Removing item 2
Removing item 4

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 2 errors from 1 contexts (suppressed: 0 from 0)
```

The stack trace is full of `std::list` internals, which is typical for this bug. Skip past the library frames to the first line in your own code: the invalid read is at `main.cpp:21` (the `++it`), and the memory was freed at `main.cpp:25` (the `erase`). Without valgrind this program usually just segfaults.

## Key Lesson
`erase()` returns an iterator to the next element; use it: `it = items.erase(it);` and skip the `++it` on that path. Other safe options are `std::remove_if` followed by `erase`, or collecting the items to remove and erasing them after the loop. This applies to `std::vector` too, where erasing invalidates every iterator past the erased element.
