// This file is used for grading -- do not modify it, except for the PIT
// interrupt-line change described in the PIT driver lab instructions. Any
// other changes will be discarded and the original file will be used when
// your lab is graded.

#include <chrono>
#include <stdio.h>
#include <sys/time.h>

#include "intc/intc.h"
#include "system.h"

#define US_PER_S 1000000
#define MS_PER_S 1000

#ifndef TEST_NONBLOCKING
#define TEST_NONBLOCKING 0
#endif

uint32_t int_mask = SYSTEM_INTC_IRQ_FIT_MASK;

int main() {
  printf("Interrupt Rate Test Application - %s Mode\n",
         TEST_NONBLOCKING ? "Non-blocking" : "Blocking");

  int err = intc_init(SYSTEM_INTC_UIO_FILE);
  if (err != 0) {
    printf("Init error (is the hardware loaded and are the udev rules installed?)\n");
    return err;
  }

  // Disable all interrupt lines
  intc_irq_disable(0xFFFFFFFF);

  // Enable interrupt lines to be tested
  intc_irq_enable(int_mask);

  // Interrupt counter
  int int_cnt = 0;

  auto start = std::chrono::high_resolution_clock::now();

  while (1) {

    // Calculate elapsed seconds
    auto end = std::chrono::high_resolution_clock::now();
    float delta_s = std::chrono::duration<float>(end - start).count();

    if (delta_s >= 1.0) {
      start = end;
      printf("Interrupt in last second: %d Avg period: %f ms\n", int_cnt,
             MS_PER_S * delta_s / int_cnt);
      int_cnt = 0;
    }

    int timeout = 0;

    if (TEST_NONBLOCKING) {
      if (intc_try_wait_for_interrupt(timeout)) {
        int_cnt++;
        intc_ack_interrupt(int_mask);
      }
    } else {
      intc_wait_for_interrupt();
      int_cnt++;
      intc_ack_interrupt(int_mask);
    }
  }

  return 0;
}
