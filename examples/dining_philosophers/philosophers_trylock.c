// Dining philosophers WITH synchronization: lock only to check and take a fork.
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define N 5 // number of philosophers (and forks)
#define MEALS 1000
#define FREE -1

// Who is holding each fork, protected by that fork's lock.
int fork_owner[N];
pthread_mutex_t fork_lock[N];

bool try_pick_up(int fork, int id) {
  bool got_it = false;
  pthread_mutex_lock(&fork_lock[fork]);
  if (fork_owner[fork] == FREE) { // check and take, both under the lock
    fork_owner[fork] = id;
    got_it = true;
  }
  pthread_mutex_unlock(&fork_lock[fork]);
  return got_it;
}

void pick_up(int fork, int id) {
  while (!try_pick_up(fork, id))
    ; // fork is busy, try again
}

void put_down(int fork) {
  pthread_mutex_lock(&fork_lock[fork]);
  fork_owner[fork] = FREE;
  pthread_mutex_unlock(&fork_lock[fork]);
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
  for (int i = 0; i < N; i++) {
    fork_owner[i] = FREE;
    pthread_mutex_init(&fork_lock[i], NULL);
  }

  for (int i = 0; i < N; i++)
    pthread_create(&threads[i], NULL, philosopher, (void *)(long)i);
  for (int i = 0; i < N; i++)
    pthread_join(threads[i], NULL);
  return 0;
}
