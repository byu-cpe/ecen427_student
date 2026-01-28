# Iterator Invalidation - Modifying Container While Iterating

## Bug Type
Modifying a container (adding, removing, or deleting elements) while iterating over it with a range-based for loop or iterator. This invalidates the iterator, leading to undefined behavior.

## Common Scenario
Looping through a list of objects, checking a condition, and removing/deleting objects that match. The removal invalidates the current iterator, causing crashes or skipped elements on the next iteration.

## Valgrind Output
```
Invalid read of size X
  at 0x...: std::__detail::_List_node_base::...
```

or may crash with no clear valgrind message (undefined behavior).

## Key Lesson
When you need to remove elements while iterating:
1. Use iterator-based loops with `it = container.erase(it)` 
2. Make a copy of the container before iterating
3. Collect items to remove, then remove them after the loop
4. Use `std::remove_if` with `erase`
