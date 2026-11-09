# Dining Philosophers

Five threads (philosophers) share five forks.  `philosophers_unsync.c` picks up
forks with no locking; `philosophers_trylock.c` gives every fork a mutex, held
only while checking and taking the fork.
Each philosopher counts the meals where a neighbor was holding one of its forks.

```
make
./philosophers_unsync
./philosophers_trylock
taskset -c 0 ./philosophers_unsync   # run on a single core
```
