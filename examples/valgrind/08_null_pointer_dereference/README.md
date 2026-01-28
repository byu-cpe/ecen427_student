# Null Pointer Dereference - Using Unset Pointers

## Bug Type
Attempting to access members or call methods on a pointer that is `nullptr`. This typically causes a segmentation fault.

## Common Scenario
A pointer member is initialized to `nullptr` and is only set under certain conditions. Later code assumes the pointer is always valid and uses it without checking.

## Valgrind Output
```
Invalid read of size X
  at 0x...: function_name (file.cpp:line)
  Address 0x0 is not stack'd, malloc'd or (recently) free'd
```

Note: Address `0x0` (or very small addresses like `0x8`) indicates a null pointer dereference.

## Key Lesson
Always check pointers before dereferencing: `if (ptr) { ptr->method(); }`. Consider using references instead of pointers when the object must always exist. In modern C++, `std::optional` can express "may or may not have a value" more safely.
