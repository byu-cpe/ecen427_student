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
    for (auto it = items.begin(); it != items.end(); ++it) {
      Item *item = *it;
      if (!item->active) {
        delete item;
        std::cout << "Removed item " << item->id << "\n"; // BUG: item was just deleted
        items.erase(it);
        return;
      }
    }
  }

private:
  std::list<Item *> items;
};

int main() {
  ItemList list;
  list.addItem(1, true);
  list.addItem(2, false);
  list.addItem(3, true);
  list.removeInactive();
  return 0;
}
