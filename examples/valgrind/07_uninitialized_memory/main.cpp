#include <iostream>

class Counter {
public:
  // BUG: count is never initialized. Should be:
  //   Counter(int max) : max(max), count(0) {}
  Counter(int max) : max(max) {}

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
