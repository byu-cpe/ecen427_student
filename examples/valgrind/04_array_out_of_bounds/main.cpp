#include <iostream>

class Inventory {
public:
  Inventory(int numSlots) : numSlots(numSlots) {
    used = new bool[numSlots];
    for (int i = 0; i < numSlots; i++)
      used[i] = false;
  }

  ~Inventory() { delete[] used; }

  void markUsed(int slot) { used[slot] = true; }

  // Find the highest-numbered slot that is in use, searching from the top.
  int lastUsedSlot() {
    for (int i = numSlots; i >= 0; i--) { // HERE
      if (used[i])
        return i;
    }
    return -1;
  }

private:
  int numSlots;
  bool *used;
};

int main() {
  Inventory inventory(5);
  inventory.markUsed(1);
  std::cout << "Last used slot: " << inventory.lastUsedSlot() << "\n";
  return 0;
}
