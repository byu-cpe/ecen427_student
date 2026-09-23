// The same loop as syscall.c, but using fread() instead of read().  fread()
// is a C library function, not a system call: it copies out of a buffer
// inside the FILE struct and only calls read() when that buffer runs dry.
//
// Usage: ./fread [CHUNK_SIZE]
//   CHUNK_SIZE  bytes requested per fread() call (default 1)
//
// Compare the system call counts:
//   strace --summary-only ./syscall 1
//   strace --summary-only ./fread 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "asyoulik.txt"
#define DEFAULT_CHUNK_SIZE 1

// Wall-clock time in seconds
static double now(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main(int argc, char *argv[]) {
  size_t chunk_size = DEFAULT_CHUNK_SIZE;
  if (argc > 2 ||
      (argc == 2 && (chunk_size = strtoul(argv[1], NULL, 10)) == 0)) {
    fprintf(stderr, "Usage: %s [CHUNK_SIZE]\n", argv[0]);
    return 1;
  }

  char *buf = malloc(chunk_size);
  if (buf == NULL) {
    perror("malloc");
    return 1;
  }

  FILE *f = fopen(FILENAME, "r");
  if (f == NULL) {
    perror("fopen " FILENAME);
    return 1;
  }

  double start = now();

  size_t total_bytes = 0;
  long num_freads = 0;
  size_t n;
  while ((n = fread(buf, 1, chunk_size, f)) > 0) {
    num_freads++;
    total_bytes += n;
  }

  double elapsed = now() - start;

  fclose(f);
  free(buf);

  fprintf(stderr,
          "Read %zu bytes with %ld fread() calls of %zu bytes in %.6f s\n",
          total_bytes, num_freads, chunk_size, elapsed);
  return 0;
}
