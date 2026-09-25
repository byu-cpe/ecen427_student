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
    // A range-based for loop uses an iterator behind the scenes. Removing the
    // current element frees the list node that hidden iterator points to, and
    // the loop then advances from the freed node.
    for (Item *item : items) {
      if (!item->active) {
        std::cout << "Removing item " << item->id << "\n";
        delete item;
        items.remove(item); // BUG: the loop's hidden iterator is now invalid
      }
    }

    // Writing the loop with an explicit iterator makes the problem visible.
    // This version has the same bug:
    //
    // for (auto it = items.begin(); it != items.end(); ++it) {
    //   if (!(*it)->active) {
    //     std::cout << "Removing item " << (*it)->id << "\n";
    //     delete *it;
    //     items.erase(it); // BUG: 'it' is now invalid, but the loop does ++it next
    //   }
    // }
    //
    // The fix: erase() returns an iterator to the next element, so use it, and
    // only ++it when nothing was erased:
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
