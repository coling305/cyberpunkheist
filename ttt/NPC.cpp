#include "NPC.h"
#include "Weapon.h"

using namespace std;

string NPC::getType() {
    return type;
}
string NPC::getName() {
    return name;
}
vector<Weapon> NPC::getWeaponry() {
    return weaponry;
}
void NPC::addWeapon(Weapon temp) {
    weaponry.emplace_back(temp);
}
void NPC::clearWeaponry() {
    weaponry.clear();
}
