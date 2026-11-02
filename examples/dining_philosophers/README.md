# Dining Philosophers

Five threads (philosophers) share five forks.  `philosophers_unsync.c` picks up
forks with no locking; `philosophers_sync.c` protects each fork with a mutex.
Each philosopher counts the meals where a neighbor was holding one of its forks.

```
make
./philosophers_unsync
./philosophers_sync
taskset -c 0 ./philosophers_unsync   # run on a single core
```
