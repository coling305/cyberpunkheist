#pragma once
#include <string>
using namespace std;

class Weapon {
    string name;
    int power = 0;
    int worth = 0;
    int initialPower = 0;
public:
    Weapon(string name, int power, int worth) {
        this->name = name;
        this->power = power;
        this->initialPower = power;
        this->worth = worth;
    }
    string getName();
    int getPower();
    int getWorth();
    int getInitialPower();
    void upgradeWeapon();
};