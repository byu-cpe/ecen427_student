/*
 * generic_uio_example.h
 *
 * ECEn 427
 * Benjamin James, Tanner Gaskin
 * BYU 2018
 */

#include <stdint.h>

/*********************************** macros ***********************************/
#define UIO_EXAMPLE_ERROR -1  // error return value
#define UIO_EXAMPLE_SUCCESS 0 // success return value
#define MMAP_OFFSET 0

/**************************** function prototypes *****************************/
// initializes the uio driver
int32_t generic_init(char devDevice[]);

// write to a register of the UIO device
void generic_write(uint32_t offset, uint32_t value);

// read from a register of the UIO device
uint32_t generic_read(uint32_t offset);

// close the UIO device
void generic_exit();