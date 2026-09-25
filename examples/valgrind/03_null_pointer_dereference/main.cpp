#include <iostream>

class Weapon {
public:
  Weapon(const char *name, int damage) : name(name), damage(damage) {}

  void fire() { std::cout << name << " fires for " << damage << " damage!\n"; }

private:
  const char *name;
  int damage;
};

class Player {
public:
  Player(const char *name) : name(name), weapon(nullptr) {}

  void equipWeapon(Weapon *w) { weapon = w; }

  void dropWeapon() {
    delete weapon;
    weapon = nullptr;
  }

  void attack() {
    std::cout << name << " attacks with ";
    weapon->fire(); // HERE
  }

private:
  const char *name;
  Weapon *weapon;
};

int main() {
  Player player("Hero");

  std::cout << "Attempting attack without weapon...\n";
  player.attack();

  player.equipWeapon(new Weapon("Sword", 10));
  player.attack();
  player.dropWeapon();

  return 0;
}
