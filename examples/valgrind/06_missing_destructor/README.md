# Missing Destructor Cleanup - Leaking Owned Objects

## Bug Type
A class that owns dynamically allocated objects (created with `new`) doesn't delete them in its destructor, causing memory leaks when the owning object is destroyed.

## Common Scenario
A container class (e.g., a game level, manager, or composite object) creates child objects with `new` and stores pointers to them. When the container is destroyed, the child objects are never freed because the destructor is empty or missing.

## Valgrind Output
```
definitely lost: X bytes in Y blocks
  at 0x...: operator new(unsigned long)
  by 0x...: ClassName::ClassName() (file.cpp:line)
```

## Key Lesson
If a class creates objects with `new`, it typically needs a destructor to `delete` them. Follow the "Rule of Three/Five" - if you need a custom destructor, you likely also need custom copy constructor and assignment operator (or delete them). Consider using smart pointers to automate cleanup.
