#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "buttons/buttons.h"
#include "system.h"

#define BUTTONS_INVALID 0xFF
#define EXIT_ERROR -1

// Print button values in binary
void print_buttons(uint8_t buttons) {
  printf("Buttons: ");

  // Loop through buttons, mask and print
  for (int8_t i = (BUTTONS_CNT - 1); i >= 0; i--) {
    printf("%d", buttons & (1 << i) ? 1 : 0);
  }
  printf("\n");
}

// Run the buttons_test application
int main() {
  printf("-------------------------------------------------------\n");
  printf("Welcome to the buttons test.\n");
  printf("When you press or release a button the new button values should be "
         "printed in binary.\n");
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
  while (1) {
    buttons = buttons_read() & BUTTONS_ALL_MASK;

    // Print only if button value has changed
    if (buttons != buttons_old) {
      print_buttons(buttons);
      buttons_old = buttons;
    }
  }
  return 0;
}