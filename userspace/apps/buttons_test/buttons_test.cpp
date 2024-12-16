#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "buttons/buttons.h"
#include "system.h"

#define BUTTONS_INVALID 0xFF
#define EXIT_ERROR -1

// Print button values in binary
void print_buttons(uint8_t buttons, bool int_pending_before_ack,
                   bool int_pending_after_ack) {}

// Run the buttons_test application
int main() {
  printf("-------------------------------------------------------\n");
  printf("Welcome to the buttons test.\n");
  printf("When you press or release a button the new button values should be "
         "printed in binary.\n\n");
  printf("After each button press or release, the program will check if an "
         "interrupt is pending,\nthen acknowledge the interrupt, then verify "
         "that the interrupt is no longer pending.\n\n");
  printf("When correctly implemented, the program should print something like "
         "the following\nafter each button press or release:\n\n");
  printf(
      "Buttons: 0001  Int pending: 1 -- Ack Interrupt -- Int pending: 0\n\n");
  printf("The buttons driver does not handle debouncing; you may "
         "see extra messages when the buttons bounce.\n");
  printf("-------------------------------------------------------\n");

  // Initialize buttons and check for error
  int32_t err = buttons_init(SYSTEM_BUTTONS_UIO_FILE);
  if (err) {
    printf("butons_init failed\n");
    exit(EXIT_ERROR);
  }

  uint8_t buttons_old = BUTTONS_INVALID;
  uint8_t buttons;

  // Loop forever
  for (;; buttons_old = buttons) {
    buttons = buttons_read() & BUTTONS_ALL_MASK;

    // Print only if button value has changed
    if (buttons != buttons_old) {

      printf("Buttons: ");
      // Loop through buttons, mask and print
      for (int8_t i = (BUTTONS_CNT - 1); i >= 0; i--) {
        printf("%d", buttons & (1 << i) ? 1 : 0);
      }

      if (buttons_old == BUTTONS_INVALID) {
        // Skip interrupt check on first loop
        printf("\n");
        continue;
      }

      // Make sure interrupt occurred
      bool int_pending = buttons_interrupt_pending();
      printf("  Int pending: %d", int_pending);
      if (!int_pending) {
        printf("\nERROR: Buttons changed, but no interrupt pending\n");
        continue;
      }

      printf(" -- Ack Interrupt -- ");
      buttons_ack_interrupt();

      int_pending = buttons_interrupt_pending();
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
