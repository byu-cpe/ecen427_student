# Null Pointer Dereference

## Bug
Calling a method through a pointer that is still `nullptr`. `Player` starts with no weapon (`weapon` is initialized to `nullptr` in the constructor), and `Player::attack()` calls `weapon->fire()` without checking.

The spot to look at is marked `// HERE` in `main.cpp`.

## Common Scenario
A pointer member is initialized to `nullptr` and only set later under certain conditions (after an "equip", a "start", the first event). Other code assumes it is always valid. The same crash happens after `dropWeapon()`, which sets the pointer back to `nullptr`.

## Valgrind Output
```
Invalid read of size 8
   at 0x1092CA: Weapon::fire() (main.cpp:7)
   by 0x1093F1: Player::attack() (main.cpp:27)
   by 0x10921F: main (main.cpp:39)
 Address 0x0 is not stack'd, malloc'd or (recently) free'd

Process terminating with default action of signal 11 (SIGSEGV)
 Access not within mapped region at address 0x0
   at 0x1092CA: Weapon::fire() (main.cpp:7)
   by 0x1093F1: Player::attack() (main.cpp:27)
   by 0x10921F: main (main.cpp:39)
```

`Address 0x0` (or a very small address like `0x8`, which is a member at a small offset from a null pointer) is the signature of a null pointer dereference. This program also crashes without valgrind; valgrind's contribution is the exact line and the call stack.

## Key Lesson
Check pointers before using them (`if (weapon) ...`), or restructure so the pointer can never be null when it is used. Notice the stack trace: the crash is inside `Weapon::fire()`, but the bug is in `Player::attack()`, one frame up.
