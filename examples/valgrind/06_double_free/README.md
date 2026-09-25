# Double Free

## Bug
Calling `delete` on the same object twice. `ItemList::remove()` deletes an item but leaves its pointer in the vector, so the destructor deletes it again.

The spot to look at is marked `// HERE` in `main.cpp`.

## Common Scenario
An object is deleted in one place (when it is "removed" or "killed"), but a container still holds the pointer. Later, cleanup code loops over the container and deletes everything.

## Valgrind Output
```
Invalid free() / delete / delete[] / realloc()
   at 0x484A61D: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x1093D9: ItemList::~ItemList() (main.cpp:14)
   by 0x1092E5: main (main.cpp:40)
 Address 0x4e20120 is 0 bytes inside a block of size 4 free'd
   at 0x484A61D: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x10955A: ItemList::remove(int) (main.cpp:22)
   by 0x1092D4: main (main.cpp:38)
 Block was alloc'd at
   at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x109454: ItemList::addItem(int) (main.cpp:17)
   by 0x1092B2: main (main.cpp:36)

Removed item 2

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

"Invalid free()" with an address that is "inside a block ... free'd" means a second delete of the same memory. Valgrind shows both the second delete (line 14, in the destructor) and the first (line 22, in `remove()`), plus where the block was allocated (line 17, in `addItem()`).

## Key Lesson
Every object needs exactly one owner responsible for deleting it. If you delete an object, remove its pointer from every container that might delete it later, or set the pointer to `nullptr` (deleting `nullptr` is safe).
