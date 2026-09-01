#include <iostream>
#include <list>

class Item {
public:
  Item(int id, bool shouldRemove = false)
      : id(id), markedForRemoval(shouldRemove) {
    std::cout << "Item " << id << " created\n";
  }
  ~Item() { std::cout << "Item " << id << " destroyed\n"; }
  int getId() { return id; }
  bool shouldBeRemoved() { return markedForRemoval; }

private:
  int id;
  bool markedForRemoval;
};

class ItemList {
public:
  void addItem(int id, bool shouldRemove = false) {
    items.push_back(new Item(id, shouldRemove));
  }

  // BUG: Modifying list while iterating with range-based for
  void removeMarkedItems() {
    for (auto item :
         items) { // Range-based for - can't modify during iteration!
      if (item->shouldBeRemoved()) {
        std::cout << "Removing item " << item->getId() << "\n";
        delete item;
        items.remove(item); // BUG: Invalidates the iterator!
      }
    }
  }

  ~ItemList() {
    for (auto item : items) {
      delete item;
    }
  }

private:
  std::list<Item *> items;
};

int main() {
  ItemList list;

  list.addItem(1, false);
  list.addItem(2, true); // Marked for removal
  list.addItem(3, false);
  list.addItem(4, true); // Marked for removal
  list.addItem(5, false);

  std::cout << "\nRemoving marked items...\n";
  list.removeMarkedItems();

  std::cout << "\nProgram ending...\n";
  return 0;
}
