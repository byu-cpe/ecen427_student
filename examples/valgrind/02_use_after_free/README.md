# Use-After-Free - Accessing Deleted Memory

## Bug Type
Accessing memory after it has been freed with `delete`. The pointer still holds the old address, but the memory is no longer valid.

## Common Scenario
Deleting an object, then trying to use that pointer for comparison, iteration, or accessing members. For example, deleting an item and then searching a list to remove it (which requires comparing against the deleted pointer).

## Valgrind Output
```
Invalid read of size X
  Address 0x... is Y bytes inside a block of size Z free'd
```

## Key Lesson
After calling `delete`, the pointer becomes a "dangling pointer." Either set it to `nullptr` immediately, or ensure you don't use it after deletion. Consider removing from containers *before* deleting.
