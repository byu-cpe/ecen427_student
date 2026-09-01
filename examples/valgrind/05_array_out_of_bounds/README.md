# Array Out-of-Bounds - Accessing Invalid Indices

## Bug Type
Reading or writing to an array index that is outside the valid range (negative, or >= array size). This accesses memory that doesn't belong to the array.

## Common Scenario
Off-by-one errors in loops, such as using `<=` instead of `<`, or starting at index `N` instead of `N-1` when iterating backwards. Also common when calculating indices based on user input or game state.

## Valgrind Output
```
Invalid read of size X
  at 0x...: function_name (file.cpp:line)
  Address 0x... is Y bytes after a block of size Z alloc'd
```

or for stack arrays (with `--stack-check`):
```
Invalid read of size X
  Address 0x... is on thread 1's stack
```

## Key Lesson
Always verify loop bounds. When iterating backwards, remember arrays are 0-indexed so the last valid index is `size - 1`. Consider using `.at()` for vectors during debugging (it throws on out-of-bounds).
