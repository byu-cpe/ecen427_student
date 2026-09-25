#include <iostream>
#include <vector>

class Item {
public:
  Item(int id) : id(id) {}
  int id;
};

class ItemList {
public:
  ~ItemList() {
    for (Item *item : items)
      delete item; // Deletes item 2 a second time!
  }

  void addItem(int id) { items.push_back(new Item(id)); }

  void remove(int id) {
    for (Item *item : items) {
      if (item->id == id) {
        delete item; // BUG: deleted, but the pointer is still in the vector
        std::cout << "Removed item " << id << "\n";
        return;
      }
    }
  }

private:
  std::vector<Item *> items;
};

int main() {
  ItemList list;
  list.addItem(1);
  list.addItem(2);
  list.addItem(3);
  list.remove(2);
  return 0;
}
