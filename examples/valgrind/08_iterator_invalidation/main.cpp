#include <iostream>
#include <list>

class Item {
public:
  Item(int id, bool active) : id(id), active(active) {}
  int id;
  bool active;
};

class ItemList {
public:
  ~ItemList() {
    for (Item *item : items)
      delete item;
  }

  void addItem(int id, bool active) { items.push_back(new Item(id, active)); }

  void removeInactive() {
    for (Item *item : items) {
      if (!item->active) {
        std::cout << "Removing item " << item->id << "\n";
        delete item;
        items.remove(item); // HERE
      }
    }

    // Explicit-iterator version 1:
    //
    // for (auto it = items.begin(); it != items.end(); ++it) {
    //   if (!(*it)->active) {
    //     std::cout << "Removing item " << (*it)->id << "\n";
    //     delete *it;
    //     items.erase(it);
    //   }
    // }
    //
    // Explicit-iterator version 2:
    //
    // for (auto it = items.begin(); it != items.end();) {
    //   if (!(*it)->active) {
    //     std::cout << "Removing item " << (*it)->id << "\n";
    //     delete *it;
    //     it = items.erase(it);
    //   } else {
    //     ++it;
    //   }
    // }
  }

private:
  std::list<Item *> items;
};

int main() {
  ItemList list;
  list.addItem(1, true);
  list.addItem(2, false);
  list.addItem(3, true);
  list.addItem(4, false);
  list.removeInactive();
  return 0;
}
