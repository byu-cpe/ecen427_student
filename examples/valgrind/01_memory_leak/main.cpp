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

  void removeItem(int id) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      if ((*it)->getId() == id) {
        items.erase(it); // HERE
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

  // Remove item 2
  manager.removeItem(2);

  std::cout << "Program ending...\n";

  return 0;
}
