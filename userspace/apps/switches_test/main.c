#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "switches/switches.h"
#include "system.h"

#define SWITCHES_INVALID 0xFF
#define EXIT_ERROR -1

// Print switch values in binary
void print_switches(uint8_t switches) {
  printf("Switches: ");

  // Print switch values
  for (int8_t i = (SWITCHES_CNT - 1); i >= 0; i--) {
    printf("%d", switches & (1 << i) ? 1 : 0);
  }
  printf("\n");
}

// Run the switches_test application
int main() {
  printf("-------------------------------------------------------\n");
  printf("Welcome to the switches test.\n");
  printf("When you move a switch the new switch values should be printed in "
         "binary.\n");
  printf("The switches do not typically bounce, so you should not see more "
         "than one message when you move a switch.\n");
  printf("-------------------------------------------------------\n");

  // Initialize switches
  int32_t err = switches_init(SYSTEM_SWITCHES_UIO_FILE);
  if (err) {
    printf("switches init failed\n");
    exit(EXIT_ERROR);
  }

  uint8_t switches_old = SWITCHES_INVALID;
  uint8_t switches;

  // Loop forever
  while (1) {
    switches = switches_read() & SWITCHES_ALL_MASK;

    // Check if the switches have changes, and print them
    if (switches != switches_old) {
      print_switches(switches);
      switches_old = switches;
    }
  }
  return 0;
}