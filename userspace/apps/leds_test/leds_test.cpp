// leds_test: a small application that exercises your buttons, switches and
// LEDs drivers.  See the Lab 2 page on the course website for details.
//
//   * The LEDs follow the buttons: LED i is on while button i is pressed.
//   * If either switch is up, the LEDs are instead the inverse of the
//     buttons: LED i is on while button i is *not* pressed.
//   * The program runs until you press Ctrl+C.

#include <stdint.h>
#include <stdio.h>

#include "buttons/buttons.h"
#include "leds/leds.h"
#include "switches/switches.h"
#include "system.h"

int main() {
  printf("leds_test: LEDs follow the buttons (inverted if a switch is up).  "
         "Press Ctrl+C to exit.\n");

  // Initialize the buttons, switches, and LEDs drivers, checking for errors.

  // Loop forever, writing the buttons (or their inverse, depending on the
  // switches) to the LEDs.
  return 0;
}
