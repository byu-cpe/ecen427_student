# Memory-Mapped Files

`learn_mmap.c` maps `hello.txt` into the program's address space with
`mmap()`, reads a byte from it, and changes another byte through the pointer.
No `read()` or `write()` is involved, yet the change shows up in the file.

```
make run      # run it and print hello.txt afterward
make trace    # same, under strace
```
