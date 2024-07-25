#include "Weapon.h"
using namespace std;

string Weapon::getName() {
    return name;
}
int Weapon::getPower() {
    return power;
}
int Weapon::getWorth() {
    return worth;
}
int Weapon::getInitialPower() {
    return initialPower;
}
void Weapon::upgradeWeapon() { // upgrade 3 times max
    power += 5;
}
