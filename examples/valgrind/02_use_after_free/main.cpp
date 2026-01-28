#include <iostream>
#include <list>

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

  // BUG: Deletes the item, then tries to access it
  void removeItem(int id) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      if ((*it)->getId() == id) {
        Item *item = *it;
        delete item; // Delete first

        // BUG: Access the deleted object!
        std::cout << "Removed item with id: " << item->getId() << "\n";

        items.erase(it);
        return;
      }
    }
  }

  ~ItemManager() {
    for (auto item : items) {
      delete item;
    }
  }

private:
  std::list<Item *> items;
};

int main() {
  ItemManager manager;

  manager.addItem(1);
  manager.addItem(2);
  manager.addItem(3);

  // This will cause use-after-free
  manager.removeItem(2);

  std::cout << "Program ending...\n";
  return 0;
}
