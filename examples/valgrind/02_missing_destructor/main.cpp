#include <iostream>
#include <vector>

class Block {
public:
  Block(int id) : id(id) { std::cout << "Block " << id << " created\n"; }
  ~Block() { std::cout << "Block " << id << " destroyed\n"; }

private:
  int id;
};

class Container {
public:
  Container() {
    std::cout << "Container created\n";
    // Create some blocks
    for (int i = 0; i < 5; i++) {
      blocks.push_back(new Block(i));
    }
  }

  // BUG: Missing destructor!
  // Should have:
  // ~Container() {
  //   for (auto block : blocks) {
  //     delete block;
  //   }
  // }

private:
  std::vector<Block *> blocks;
};

int main() {
  std::cout << "Creating container...\n";
  Container *container = new Container();

  std::cout << "\nDeleting container...\n";
  delete container; // Container deleted, but its blocks are leaked!

  std::cout << "\nProgram ending...\n";
  return 0;
}
