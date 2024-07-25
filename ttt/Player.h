#include <vector>
#include "Weapon.h"
using namespace std;

class Player {
    string name;
    int lives = 0;
    int money = 0;
    int successfulHeists = 0;
    int moneyFromHeists = 0;
    int weaponsPurchased = 0;
    int weaponsSold = 0;
    vector<Weapon> inventory;
public:
    Player(string name, int lives) {
        this->name = name;
        this->lives = lives;
        if (lives == 1) {this->money = 2500;}
        else if (lives == 2) {this->money = 6000;}
        else if (lives == 3) {this->money = 15000;}
        this->inventory.emplace_back("Neon Stinger", 75, 0);
    }
    string getName();
    int getLives();
    int getMoney();
    void addMoney(int money);
    void loseLife();
    void removeWeapon(int itr);
    void addItemToInventory(Weapon temp);
    void buyWeapon(int money);
    void upgradeWeapon(int itr);
    void heistSuccessful();
    int getSuccessfulHeists();
    void addMoneyFromHeists(int money);
    int getMoneyFromHeists();
    void addWeaponsPurchased();
    int getWeaponsPurchased();
    void addWeaponsSold();
    int getWeaponsSold();
    vector<Weapon> getInventory();
};