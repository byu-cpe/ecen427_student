# Memory Leak - Forgetting to Free Memory

## Bug Type
Memory leak caused by allocating memory with `new` but never calling `delete`.

## Common Scenario
Managing a collection of dynamically allocated objects (e.g., a list of items). When removing an item from the collection, the programmer removes the pointer from the list but forgets to `delete` the object itself.

## Valgrind Output
```
definitely lost: X bytes in Y blocks
```

## Key Lesson
Every `new` must have a corresponding `delete`. When removing objects from containers, always free the memory before (or after) removing the pointer from the container.
