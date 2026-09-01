#include <iostream>
#include <vector>

class Item {
public:
  Item(int id) : id(id) { std::cout << "Item " << id << " created\n"; }
  ~Item() { std::cout << "Item " << id << " destroyed\n"; }
  int getId() { return id; }

private:
  int id;
};

class ItemManager {
public:
  void addItem(int id) { items.push_back(new Item(id)); }

  // This function deletes an item immediately
  void killItem(int id) {
    for (auto &item : items) {
      if (item && item->getId() == id) {
        delete item;
        // BUG: We delete but don't remove from vector or set to nullptr
        // The pointer is still in the vector!
        std::cout << "Killed item " << id << "\n";
        return;
      }
    }
  }

  // BUG: Destructor tries to delete all items, including already-deleted ones
  ~ItemManager() {
    std::cout << "ItemManager destructor called\n";
    for (auto item : items) {
      delete item; // Double free if item was already killed!
    }
  }

private:
  std::vector<Item *> items;
};

int main() {
  ItemManager manager;

  manager.addItem(1);
  manager.addItem(2);
  manager.addItem(3);

  // Kill item 2 - this deletes it
  manager.killItem(2);

  std::cout << "Program ending...\n";

  // When manager is destroyed, it will try to delete item 2 again!
  return 0;
}
