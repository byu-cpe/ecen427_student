// This file is used for grading -- do not modify it. Any changes will be
// discarded and the original file will be used when your lab is graded.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "switches/switches.h"
#include "system.h"

#define SWITCHES_INVALID 0xFF
#define EXIT_ERROR -1

// Print switch values in binary
void print_switches(uint8_t switches, bool int_pending_before_ack,
                    bool int_pending_after_ack) {}

// Run the switches_test application
int main() {
  printf("-------------------------------------------------------\n");
  printf("Welcome to the switches test.\n");
  printf("When you flip a switch the new switch values should be printed in "
         "binary.\n\n");
  printf("After each switch flip, the program will check if an interrupt is "
         "pending,\nthen acknowledge the interrupt, then verify that the "
         "interrupt is no longer pending.\n\n");
  printf("When correctly implemented, the program should print something like "
         "the following\nafter each switch flip:\n\n");
  printf(
      "Switches: 0001  Int pending: 1 -- Ack Interrupt -- Int pending: 0\n\n");
  printf("The switches driver does not handle debouncing; you may "
         "see extra messages when the switches bounce.\n\n");
  printf("If the power jumper is loose, moving the switches may power cycle "
         "the board.\nIf you notice that happen, throw that jumper out and "
         "get a new one from the\ndrawer on the left at the back of the "
         "room.\n");
  printf("-------------------------------------------------------\n");

  // Initialize switches and check for error
  int32_t err = switches_init(SYSTEM_SWITCHES_UIO_FILE);
  if (err) {
    printf("switches_init failed\n");
    exit(EXIT_ERROR);
  }

  uint8_t switches_old = SWITCHES_INVALID;
  uint8_t switches;

  // Loop forever
  for (;; switches_old = switches) {
    switches = switches_read() & SWITCHES_ALL_MASK;

    // Print only if switch value has changed
    if (switches != switches_old) {

      printf("Switches: ");
      // Loop through switches, mask and print
      for (int8_t i = (SWITCHES_CNT - 1); i >= 0; i--) {
        printf("%d", switches & (1 << i) ? 1 : 0);
      }

      if (switches_old == SWITCHES_INVALID) {
        // Skip interrupt check on first loop
        printf("\n");
        continue;
      }

      // Make sure interrupt occurred
      bool int_pending = switches_interrupt_pending();
      printf("  Int pending: %d", int_pending);
      if (!int_pending) {
        printf("\nERROR: Switches changed, but no interrupt pending\n");
        continue;
      }

      printf(" -- Ack Interrupt -- ");
      switches_ack_interrupt();

      int_pending = switches_interrupt_pending();
      printf("Int pending: %d", int_pending);
      if (int_pending) {
        printf("\nERROR: Interrupt still pending after ack\n");
        continue;
      }

      printf("\n");
    }
  }
  return 0;
}
