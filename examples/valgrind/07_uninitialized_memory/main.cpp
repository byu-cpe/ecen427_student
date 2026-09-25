#include <iostream>

class Counter {
public:
  Counter(int max) : max(max) {} // HERE

  // Returns true every max-th call.
  bool tick() {
    count++;
    if (count >= max) {
      count = 0;
      return true;
    }
    return false;
  }

private:
  int max;
  int count;
};

int main() {
  Counter counter(10);
  for (int i = 0; i < 30; i++) {
    if (counter.tick())
      std::cout << "Counter expired on tick " << i << "\n";
  }
  return 0;
}
