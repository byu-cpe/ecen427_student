// Dining philosophers with NO synchronization.
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 5 // number of philosophers (and forks)
#define MEALS 1000
#define FREE -1

// Who is holding each fork. volatile: re-read memory every time we check.
volatile int fork_owner[N];

void pick_up(int fork, int id) {
  while (fork_owner[fork] != FREE)
    ; // wait until the fork is free
  fork_owner[fork] = id;
}

void put_down(int fork) {
  fork_owner[fork] = FREE;
}

void *philosopher(void *arg) {
  int id = (long)arg;
  int first = id, second = (id + 1) % N;
  if (second < first) { // lower-numbered fork first, to avoid deadlock
    first = second;
    second = id;
  }

  int shared = 0;
  for (int meal = 0; meal < MEALS; meal++) {
    pick_up(first, id);
    pick_up(second, id);
    usleep(1); // eat
    if (fork_owner[first] != id || fork_owner[second] != id)
      shared++; // someone else has our fork!
    put_down(second);
    put_down(first);
  }
  printf("Philosopher %d: %d meals with a shared fork\n", id, shared);
  return NULL;
}

int main() {
  pthread_t threads[N];
  for (int i = 0; i < N; i++)
    fork_owner[i] = FREE;

  for (int i = 0; i < N; i++)
    pthread_create(&threads[i], NULL, philosopher, (void *)(long)i);
  for (int i = 0; i < N; i++)
    pthread_join(threads[i], NULL);
  return 0;
}
