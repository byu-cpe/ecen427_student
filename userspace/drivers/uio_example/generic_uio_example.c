

/*
 * Generic UIO device driver
 * This driver is intended as an example of how to interact with a UIO device.
 * It contains only the boiler-plate necessary to open, close, read from, and
 *  write to a UIO device.  There are usually additional initialization steps
 *  that must be performed before you can actually use a UIO device.
 *
 * ECEn 427
 * Benjamin James, Tanner Gaskin
 * BYU 2018
 */

#include "generic_uio_example.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define UIO_EXAMPLE_MMAP_SIZE 0x1000 // size of memory to allocate
#define OPEN_ERROR -1                // open() returns -1 on error

/********************************** globals ***********************************/
static int f;     // this is a file descriptor that describes an open UIO device
static char *ptr; // this is the virtual address of the UIO device registers

/********************************* functions **********************************/
// initializes the uio driver, returns -1 if failed in error, 0 otherwise
int32_t generic_init(char devDevice[]) {

  // open the device
  f = open(devDevice, O_RDWR);
  if (f == OPEN_ERROR) {
    printf("uio example init error -- did you forget to sudo?\n");
    return UIO_EXAMPLE_ERROR;
  }

  // memory map the physical address of the hardware into virtual address space
  ptr = mmap(NULL, UIO_EXAMPLE_MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, f,
             MMAP_OFFSET);
  if (ptr == MAP_FAILED) {
    return UIO_EXAMPLE_ERROR;
  }

  /* put hardware setup here */

  return UIO_EXAMPLE_SUCCESS;
}

// write to a register of the UIO device
void generic_write(uint32_t offset, uint32_t value) {
  // the address is cast as a pointer so it can be dereferenced
  *((volatile uint32_t *)(ptr + offset)) = value;
}

// read from a register of the UIO device
uint32_t generic_read(uint32_t offset) {
  return *((volatile uint32_t *)(ptr + offset));
}

// close the UIO device
//	this function must be called after all read/write operations are done
//	to properly unmap the memory and close the file descriptor
void generic_exit() {
  munmap(ptr, UIO_EXAMPLE_MMAP_SIZE);
  close(f);
}