# Array Out-of-Bounds

## Bug
An off-by-one error in a loop that walks an array backwards. The loop starts at `numSlots` instead of `numSlots - 1`, so the first iteration reads one element past the end of the array.

## Common Scenario
Using `<=` instead of `<`, or starting a backwards loop at `size` instead of `size - 1`.

## Valgrind Output
```
Invalid read of size 1
   at 0x1093AD: Inventory::lastUsedSlot() (main.cpp:18)
   by 0x10924E: main (main.cpp:32)
 Address 0x4e20085 is 0 bytes after a block of size 5 alloc'd
   at 0x48485C3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
   by 0x1092F8: Inventory::Inventory(int) (main.cpp:6)
   by 0x109215: main (main.cpp:30)

Last used slot: 1

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

"0 bytes after a block of size 5 alloc'd" means the read landed immediately past the end of a 5-byte heap array, and valgrind tells you where that array was allocated. The program prints the right answer and exits normally, so without valgrind you would never know.

## Key Lesson
Arrays are 0-indexed, so the last valid index is `size - 1`. Note that valgrind only catches out-of-bounds accesses on heap memory (`new`/`malloc`); an overrun of a local array on the stack usually goes unreported.
