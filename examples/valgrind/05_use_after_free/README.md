# Use-After-Free

## Bug
Accessing an object after it has been deleted. The pointer still holds the old address, but the memory is no longer valid.

The spot to look at is marked `// HERE` in `main.cpp`.

## Common Scenario
Deleting an object and then using it in the very next line: printing one of its fields, comparing it, or removing it from a container using a value read from it.

## Valgrind Output
```
Invalid read of size 4
   at 0x1095FF: ItemList::removeInactive() (main.cpp:25)
   by 0x1092DE: main (main.cpp:41)
 Address 0x4e20130 is 0 bytes inside a block of size 8 free'd
   at 0x484A61D: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x1095DE: ItemList::removeInactive() (main.cpp:24)
   by 0x1092DE: main (main.cpp:41)
 Block was alloc'd at
   at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x1094E9: ItemList::addItem(int, bool) (main.cpp:18)
   by 0x1092BC: main (main.cpp:39)

Removed item 2

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

Valgrind gives three locations: where the bad read happened (line 25), where the memory was freed (line 24), and where it was originally allocated (line 18, in `addItem()`, called from line 39). The program prints "Removed item 2" and looks fine, because the freed memory usually still holds the old value.

## Key Lesson
After `delete`, the pointer is dangling. Do everything you need with the object first, then delete it last. Setting the pointer to `nullptr` right after `delete` turns a silent use-after-free into an obvious crash.
