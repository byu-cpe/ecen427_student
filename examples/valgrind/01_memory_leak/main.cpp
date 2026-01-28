#include <iostream>
#include <list>

// A simple Item class
class Item {
public:
  Item(int id) : id(id) { std::cout << "Item " << id << " created\n"; }
  ~Item() { std::cout << "Item " << id << " destroyed\n"; }
  int getId() { return id; }

private:
  int id;
};

// A manager class that holds a collection of Items
class ItemManager {
public:
  void addItem(int id) { items.push_back(new Item(id)); }

  // BUG: This function removes the item from the list but doesn't delete it!
  void removeItem(int id) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      if ((*it)->getId() == id) {
        // Missing: delete *it;
        items.erase(it);
        std::cout << "Removed item " << id << " from list\n";
        return;
      }
    }
  }

  ~ItemManager() {
    // Clean up remaining items
    for (auto item : items) {
      delete item;
    }
  }

private:
  std::list<Item *> items;
};

int main() {
  ItemManager manager;

  // Add some items
  manager.addItem(1);
  manager.addItem(2);
  manager.addItem(3);

  // Remove item 2 - this will leak memory!
  manager.removeItem(2);

  std::cout << "Program ending...\n";

  // When manager goes out of scope, it will delete items 1 and 3,
  // but item 2 was already removed from the list (without being deleted)
  return 0;
}
