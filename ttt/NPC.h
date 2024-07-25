#include <iostream>
#include "Weapon.h"
#include <vector>
using namespace std;

class NPC {
    string type;
    string name;
    vector<Weapon> weaponry;
public:
    NPC(string type, string name) {
        this->type = type;
        this->name = name;
    }
    string getType();
    string getName();
    vector<Weapon> getWeaponry();
    void addWeapon(Weapon temp);
    void clearWeaponry();
};