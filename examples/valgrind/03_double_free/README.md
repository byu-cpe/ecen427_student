# Double Free - Deleting Memory Twice

## Bug Type
Calling `delete` on the same memory address more than once. This corrupts the heap and leads to undefined behavior.

## Common Scenario
An object is deleted in one place (e.g., when it's "killed" or removed), but the pointer remains in a container. Later, a destructor or cleanup function iterates through the container and tries to delete all objects again.

## Valgrind Output
```
Invalid free() / delete / delete[] / realloc()
  Address 0x... is Y bytes inside a block of size Z free'd
```

## Key Lesson
Track ownership clearly. If an object is deleted somewhere, remove it from all containers that might try to delete it later. Consider using smart pointers (`std::unique_ptr`) to enforce single ownership.
