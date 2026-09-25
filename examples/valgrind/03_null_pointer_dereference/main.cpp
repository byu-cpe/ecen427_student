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

  // BUG: Doesn't check if weapon is nullptr before using it
  void attack() {
    std::cout << name << " attacks with ";
    weapon->fire(); // BUG: weapon might be nullptr!
  }

private:
  const char *name;
  Weapon *weapon;
};

int main() {
  Player player("Hero");

  // Player has no weapon yet, but tries to attack
  std::cout << "Attempting attack without weapon...\n";
  player.attack(); // CRASH: weapon is nullptr!

  // This code won't be reached
  player.equipWeapon(new Weapon("Sword", 10));
  player.attack();
  player.dropWeapon();

  return 0;
}
