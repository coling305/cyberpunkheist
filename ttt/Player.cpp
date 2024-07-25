#include "Player.h"
using namespace std;

string Player::getName() {
    return name;
}
int Player::getLives() {
    return lives;
}
int Player::getMoney() {
    return money;
}
void Player::addItemToInventory(Weapon temp) {
    inventory.push_back(temp);
}
vector<Weapon> Player::getInventory() {
    return inventory;
}
void Player::addMoney(int money) {
    this->money += money;
}
void Player::loseLife() {
    lives--;
}
void Player::removeWeapon(int itr) {
    inventory.erase(inventory.begin() + itr);
}
void Player::buyWeapon(int money) {
    this->money -= money;
}
void Player::upgradeWeapon(int itr) {
    inventory[itr].upgradeWeapon();
}
void Player::heistSuccessful() {
    successfulHeists++;
}
int Player::getSuccessfulHeists() {
    return successfulHeists;
}
void Player::addMoneyFromHeists(int money) {
    moneyFromHeists += money;
}
int Player::getMoneyFromHeists() {
    return moneyFromHeists;
}
void Player::addWeaponsPurchased() {
    weaponsPurchased++;
}
int Player::getWeaponsPurchased() {
    return weaponsPurchased;
}
void Player::addWeaponsSold() {
    weaponsSold++;
}
int Player::getWeaponsSold() {
    return weaponsSold;
}
