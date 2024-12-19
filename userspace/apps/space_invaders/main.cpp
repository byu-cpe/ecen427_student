#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <vector>

#include "Colors.h"
#include "Gameplay.h"
#include "Globals.h"
#include "Graphics.h"
#include "buttons/buttons.h"
#include "intc/intc.h"
#include "switches/switches.h"
#include "system.h"

int main() {
  srand(time(NULL));

  Graphics &graphics = Globals::getGraphics();
  Sprites &sprites = Globals::getSprites();
  buttons_init(SYSTEM_BUTTONS_UIO_FILE);
  switches_init(SYSTEM_SWITCHES_UIO_FILE);
  intc_init(SYSTEM_INTC_UIO_FILE);

  Globals::setBackgroundColor(Colors::BLACK);
  graphics.fillScreen(Globals::getBackgroundColor());

  // Initialize gameplay
  Gameplay gameplay;
  gameplay.drawInit();

  // Setup Interrupts
  intc_irq_enable(SYSTEM_INTC_IRQ_FIT_MASK);
  intc_enable_uio_interrupts();

  // Handled, missed interrupts
  int missed_interrupts = 0;
  int loop_count = 0;

  double last_printed_time = 0;

  // Track time
  auto start_interval = std::chrono::high_resolution_clock::now();
  auto end_interval = std::chrono::high_resolution_clock::now();

  // Interrupt loop
  std::vector<double> times;

  // How often to print the loop statistics
  constexpr double PRINT_INTERVAL_S = 5.0;

  while (1) {
    loop_count++;

    uint32_t mask = intc_pending_nonblocking(0);
    if (mask) {
      missed_interrupts++;
    } else {
      // Comment out to run the game as fast as possible
      mask = intc_wait_for_interrupt();
    }

    //////////// Loop timing statistics ////////////
    auto now = std::chrono::high_resolution_clock::now();

    // Record the time it took to run the loop
    auto last_loop_time =
        std::chrono::duration<float>(now - end_interval).count();
    times.push_back(last_loop_time);

    // Check how long this interval has been running
    end_interval = now;
    float delta_s =
        std::chrono::duration<float>(end_interval - start_interval).count();
    if (delta_s >= PRINT_INTERVAL_S) {
      // Print statistics of this interval
      start_interval = end_interval;
      printf("Total missed ints: %d ", missed_interrupts);
      printf("Loop iterations: %d ", loop_count);
      printf("Avg s/loop: %f ", delta_s / loop_count);
      printf("Max s/loop: %f\n", *std::max_element(times.begin(), times.end()));
      loop_count = 0;
      times.clear();
    }

    // Handle the interrupt, and re-enable interrupts
    if (mask & SYSTEM_INTC_IRQ_FIT_MASK)
      intc_ack_interrupt(mask);
    intc_enable_uio_interrupts();

    // Tick the gameplay
    gameplay.tick();

    // Exit game loop on gameover
    if (gameplay.isGameOver())
      break;
  }

  // Draw Game Over
  graphics.fillScreen(Globals::getBackgroundColor());
  graphics.drawStrCentered("GAME OVER", 200, 10, Colors::WHITE, Colors::BLACK);
}