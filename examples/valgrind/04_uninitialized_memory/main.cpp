#include <iostream>

class Counter {
public:
  // BUG: tickCount is not initialized!
  Counter(int maxCount) : maxCount(maxCount) {
    // Forgot to initialize tickCount!
    // Should be: Counter(int maxCount) : maxCount(maxCount), tickCount(0) {}
  }

  bool tick() {
    tickCount++; // Using uninitialized value!
    if (tickCount >= maxCount) {
      std::cout << "Counter reached max after " << tickCount << " ticks\n";
      tickCount = 0;
      return true;
    }
    return false;
  }

private:
  int maxCount;
  int tickCount; // Not initialized in constructor!
};

int main() {
  // Allocate buffer with garbage values
  // unsigned char buffer[sizeof(Counter) + 100];
  // for (unsigned int i = 0; i < sizeof(buffer); i++) {
  //   buffer[i] = 0xAA; // Fill with non-zero garbage
  // }

  // Use placement new to construct Counter in the garbage-filled buffer
  Counter counter(10);

  std::cout << "Ticking counter...\n";

  // This loop may behave unpredictably
  for (int i = 0; i < 20; i++) {
    if (counter.tick()) {
      std::cout << "Counter triggered!\n";
    }
  }

  return 0;
}
