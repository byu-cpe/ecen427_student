#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  // mmap the hello.txt file
  int fd = open("hello.txt", O_RDWR);

  char *data = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  printf("%c\n", data[0]);
  data[4] = 'X';

  munmap(data, 1024);
  close(fd);
}