// Demonstrates how the buffer size passed to read() changes the number of
// system calls a program makes, and how long it takes to run.
//
// Usage: ./syscall [BUFFER_SIZE] [-p]
//   BUFFER_SIZE  bytes requested per read() call (default 100)
//   -p           echo the file to stdout, one write() per read()
//
// Try it under strace to count the system calls:
//   strace --summary-only ./syscall 1
//   strace --summary-only ./syscall 4096

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FILENAME "asyoulik.txt"
#define DEFAULT_BUF_SIZE 100

// Wall-clock time in seconds
static double now(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec / 1e9;
}

static void usage(const char *prog) {
  fprintf(stderr, "Usage: %s [BUFFER_SIZE] [-p]\n", prog);
  exit(1);
}

int main(int argc, char *argv[]) {
  size_t buf_size = DEFAULT_BUF_SIZE;
  int echo = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-p") == 0) {
      echo = 1;
    } else {
      buf_size = strtoul(argv[i], NULL, 10);
      if (buf_size == 0)
        usage(argv[0]);
    }
  }

  char *buf = malloc(buf_size);
  if (buf == NULL) {
    perror("malloc");
    return 1;
  }

  int fd = open(FILENAME, O_RDONLY);
  if (fd < 0) {
    perror("open " FILENAME);
    return 1;
  }

  double start = now();

  size_t total_bytes = 0;
  long num_reads = 0;
  ssize_t n;
  while ((n = read(fd, buf, buf_size)) > 0) {
    num_reads++;
    total_bytes += n;
    if (echo && write(STDOUT_FILENO, buf, n) != n) {
      perror("write");
      return 1;
    }
  }

  double elapsed = now() - start;

  if (n < 0)
    perror("read");

  close(fd);
  free(buf);

  // Report on stderr so it doesn't mix with the echoed file on stdout
  fprintf(stderr,
          "Read %zu bytes with %ld read() calls of %zu bytes in %.6f s\n",
          total_bytes, num_reads, buf_size, elapsed);
  return 0;
}
