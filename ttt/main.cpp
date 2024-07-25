#include <iostream>
#include <fstream>
#include "Player.h"
#include "Weapon.h"
#include "NPC.h"
#include "Bank.h"
#include <vector>
#include <ctime> 
#include <cstdlib> 
using namespace std;

vector<vector<string>> readStatsFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<string>> stats;
    if (!file.is_open()) {
        return stats;
    }
    string line;
    while (getline(file, line)) {
        vector<string> row;
        size_t start = 0, end = 0;
        while ((end = line.find('\t', start)) != string::npos) {
            row.push_back(line.substr(start, end - start));
            start = end + 1;
        }
        row.push_back(line.substr(start));
        stats.push_back(row);
    }
    file.close();
    return stats;
}
void writeStatsToFile(const string& filename, const vector<vector<string>>& stats) {
    ofstream file(filename);
    for (const auto& row : stats) {
        for (int i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << '\t';
            }
        }
        file << '\n';
    }
    file.close();
}
void Initialize(char map[], bool isBank[], bool isArmsDealer[], vector<Bank> &banks) {
    srand(time(0));
    for (int i = 0; i < 144; i++) {
        Bank temp(0, 0, 0);
        map[i] = '-';
        isBank[i] = false;
        isArmsDealer[i] = false;
        banks.push_back(temp);
    }
    for (int i = 0; i < 7;) {
        int temp = rand() % 132;
        if (map[temp] == '-') {
            map[temp] = 'B';
            isBank[temp] = true;
            banks[temp] = Bank((rand() % 10) + 1, (rand() % 49001) + 1000, (rand() % 5) + 1);
            i++;
        }
    }
    map[137] = 'X';
}
void printMap(char map[]) {
    cout << "======MAP=======" << endl;
    for (int i = 0; i < 144; i++) {
        if ((i % 12) == 0) {cout << "| ";}
        cout << map[i];
        if (((i + 1) % 12) == 0) {cout << " |" << endl;}
    }
    cout << "================" << endl;
    cout << "| 'X': You | 'B': Bank | 'A': Arms Dealer | '-': Empty Space |" << endl << endl;
}
void Move(char map[], bool isBank[], bool isArmsDealer[], int &pos) {           // While loop
    string option;
    while (true) {
        printMap(map);
        cout << "Choose direction to move in (only input a valid number)" << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "1. Up" << endl;
        cout << "2. Down" << endl;
        cout << "3. Left" << endl;
        cout << "4. Right" << endl;
        cout << "5. Exit" << endl;
        cin >> option;
        if (option == "1") {
            if ((pos - 12) < 0) {}
            else {
                if (isBank[pos]) {map[pos] = 'B';}
                else if (isArmsDealer[pos]) {map[pos] = 'A';}
                else {map[pos] = '-';}
                pos -= 12;
                map[pos] = 'X';
            }
        }
        else if (option == "2") {
            if ((pos + 12) > 143) {}
            else {
                if (isBank[pos]) {map[pos] = 'B';}
                else if (isArmsDealer[pos]) {map[pos] = 'A';}
                else {map[pos] = '-';}
                pos += 12;
                map[pos] = 'X';
            }
        }
        else if (option == "3") {
            if (((pos - 1) < 0) || ((pos % 12) == 0)) {}
            else {
                if (isBank[pos]) {map[pos] = 'B';}
                else if (isArmsDealer[pos]) {map[pos] = 'A';}
                else {map[pos] = '-';}
                pos -= 1;
                map[pos] = 'X';
            }
        }
        else if (option == "4") {
            if (((pos + 1) > 143) || (((pos + 1) % 12) == 0)) {}
            else {
                if (isBank[pos]) {map[pos] = 'B';}
                else if (isArmsDealer[pos]) {map[pos] = 'A';}
                else {map[pos] = '-';}
                pos += 1;
                map[pos] = 'X';
            }
        }
        else if (option == "5") {break;}
        else {cout << "Not a valid integer!";}
    }
}
void helpArmsDealer(char map[], bool isArmsDealer[], int &armsPos, int &pos) {
    if (armsPos != -1) {
        isArmsDealer[armsPos] = false;
        if (pos != armsPos) {map[armsPos] = '-';}
    }
    srand(time(0));
    while (true) {
        armsPos = rand() % 132;
        if (!((map[armsPos] == 'X') || (map[armsPos] == 'B'))) {
            isArmsDealer[armsPos] = true;
            map[armsPos] = 'A';
            break;
        }
    }
}
void callArmsDealer(char map[], bool isArmsDealer[], int &armsPos, int &pos, Player &main, NPC &armsDealer) {
    string option;
    cout << "==================Call Menu=================" << endl;
    cout << "Select an option (only input a valid number)" << endl;
    cout << "1. Low-Tier Arms Dealer" << endl;
    cout << "2. Mid-Tier Arms Dealer" << endl;
    cout << "3. High-Tier Arms Dealer" << endl;
    cout << "4. Exit" << endl;
    cin >> option;
    if (option == "1") {
        if (main.getMoney() >= 2500) {
            armsDealer.clearWeaponry();
            armsDealer = NPC("low", "R2-D2");
            armsDealer.addWeapon(Weapon("Peashooter", 10, 2500));
            armsDealer.addWeapon(Weapon("Zipgun", 20, 3000));
            armsDealer.addWeapon(Weapon("Stinger", 30, 4000));
            armsDealer.addWeapon(Weapon("Popshot", 40, 4500));
            armsDealer.addWeapon(Weapon("Sparkgun", 50, 5000));
            cout << "===================" << endl;
            if (armsPos == -1) {cout << "Arms dealer called!" << endl;}
            else {cout << "Arms dealer replaced!" << endl;}
            cout << "---------------------" << endl << endl;
            helpArmsDealer(map, isArmsDealer, armsPos, pos);
        }
        else {
            cout << "=========================================================" << endl;
            cout << "You must have at least $2500 for the low-tier arms dealer" << endl;
            cout << "---------------------------------------------------------" << endl << endl;
            callArmsDealer(map, isArmsDealer, armsPos, pos, main, armsDealer);
        }
    }
    else if (option == "2") {
        if (main.getMoney() >= 6000) {
            armsDealer.clearWeaponry();
            armsDealer = NPC("mid", "C3P0");
            armsDealer.addWeapon(Weapon("Blaze Blaster", 55, 6000));
            armsDealer.addWeapon(Weapon("Pulse Rifle", 60, 7000));
            armsDealer.addWeapon(Weapon("Shockwave", 65, 8000));
            armsDealer.addWeapon(Weapon("Ionizer", 70, 9000));
            armsDealer.addWeapon(Weapon("Grit Gun", 75, 10000));
            cout << "===================" << endl;
            if (armsPos == -1) {cout << "Arms dealer called!" << endl;}
            else {cout << "Arms dealer replaced!" << endl;}
            cout << "-------------------" << endl << endl;
            helpArmsDealer(map, isArmsDealer, armsPos, pos);
        }
        else {
            cout << "=========================================================" << endl;
            cout << "You must have at least $6000 for the low-tier arms dealer" << endl;
            cout << "---------------------------------------------------------" << endl << endl;
            callArmsDealer(map, isArmsDealer, armsPos, pos, main, armsDealer);
        }
    }
    else if (option == "3") {
        if (main.getMoney() >= 15000) {
            armsDealer.clearWeaponry();
            armsDealer = NPC("high", "BB8");
            armsDealer.addWeapon(Weapon("Thunderstrike", 80, 15000));
            armsDealer.addWeapon(Weapon("Hellfire Cannon", 85, 20000));
            armsDealer.addWeapon(Weapon("Oblivion", 90, 25000));
            armsDealer.addWeapon(Weapon("Dragon's Breath", 95, 30000));
            armsDealer.addWeapon(Weapon("Terminator", 100, 50000));
            cout << "=====================" << endl;
            if (armsPos == -1) {cout << "Arms dealer called!" << endl;}
            else {cout << "Arms dealer replaced!" << endl;}
            cout << "---------------------" << endl << endl;
            helpArmsDealer(map, isArmsDealer, armsPos, pos);
        }
        else {
            cout << "=========================================================" << endl;
            cout << "You must have at least $15000 for the low-tier arms dealer" << endl;
            cout << "---------------------------------------------------------" << endl << endl;
            callArmsDealer(map, isArmsDealer, armsPos, pos, main, armsDealer);
        }
    }
    else if (option == "4") {}
    else {
        cout << "====================================" << endl;
        cout << "INVALID INPUT, INPUT A VALID OPTION!" << endl;
        cout << "------------------------------------" << endl << endl;
        callArmsDealer(map, isArmsDealer, armsPos, pos, main, armsDealer);
    }
}
void Inventory(vector<Weapon> inventory) {
    string option;
    cout << "==========Arsenal==========" << endl;
    for (int i = 0; i < inventory.size(); i++) {
        cout << "Weapon #" << i + 1 << ": " << inventory[i].getName() << endl;
        cout << "Power: " << inventory[i].getPower() << endl;
        cout << "Worth: $" << inventory[i].getWorth() << endl;
        cout << "---------------------------" << endl;
    }
    while (true) {
        cout << "Input \"1\" to exit arsenal" << endl;
        cin >> option;
        if (option == "1") {break;}
        else {cout << "INVALID INPUT, INPUT A VALID OPTION!" << endl;}
    }
}
void printStats(Player temp) {
    cout << "============" << endl;
    cout << "Player stats" << endl;
    cout << "------------" << endl;
    cout << "Name: " << temp.getName() << endl;
    cout << "Money: $" << temp.getMoney() << endl;
    cout << "Lives left: " << temp.getLives() << endl;
    cout << "Heists completed: " << temp.getSuccessfulHeists() << endl;
    cout << "Total earned from heists: $" << temp.getMoneyFromHeists() << endl;
    cout << "Number of weapons purchased: " << temp.getWeaponsPurchased() << endl;
    cout << "Number of weapons sold: " << temp.getWeaponsSold() << endl;
}
void Interact(char map[], bool isBank[], bool isArmsDealer[], NPC armsDealer, int &pos, Player &main, vector<Bank> &banks) {
    string option;
    if (isBank[pos]) {
        cout << "============================================" << endl;
        cout << "Select an option (only input a valid number)" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "1. Gather Intel" << endl;
        cout << "2. Rob Bank" << endl;
        cout << "3. Exit" << endl;
        cin >> option;
        if (option == "1") {
            cout << "=====================================" << endl;
            cout << "Intel: " << endl;
            cout << "Police nearby (1-10): " << banks[pos].getPoliceNearby() << endl;
            cout << "Money to steal ($1000-$50000): $" << banks[pos].getMoneyToSteal() << endl;
            cout << "Vault strength (1-5): " << banks[pos].getVaultStrength() << endl;
            cout << "-------------------------------------" << endl << endl;
            Interact(map, isBank, isArmsDealer, armsDealer, pos, main, banks);
        }
        else if (option == "2") {
            srand(time(0));
            int totalWeaponPower = 0;
            bool success = true;
            for (int i = 0; i < main.getInventory().size(); i++) {
                totalWeaponPower += main.getInventory()[i].getPower();
            }
            if (banks[pos].getPoliceNearby() >= ((rand() % 40) + 1)) {success = false;}
            else if (banks[pos].getVaultStrength() >= ((rand() % 20) + 1)) {success = false;}
            else if (totalWeaponPower <= (rand() % 200)) {success = false;}
            if (success) {
                main.heistSuccessful();
                main.addMoney(banks[pos].getMoneyToSteal());
                main.addMoneyFromHeists(banks[pos].getMoneyToSteal());
                cout << "=========================" << endl;
                cout << "The heist was successful!" << endl;
                cout << "=========================" << endl;
                while (true) {
                    cout << "Input \"1\" to continue" << endl;
                    cin >> option;
                    if (option == "1") {break;}
                    else {cout << "INVALID INPUT, INPUT A VALID OPTION!" << endl;}
                }
            }
            else {
                main.loseLife();
                main.removeWeapon(0);
                cout << "=========================" << endl;
                cout << "The heist was a failure!" << endl;
                cout << "=========================" << endl;
                cout << "You lost a life, and a weapon was seized!" << endl;

                while (true) {
                    cout << "Input \"1\" to continue" << endl;
                    cin >> option;
                    if (option == "1") {break;}
                    else {cout << "INVALID INPUT, INPUT A VALID OPTION!" << endl;}
                }
                if (main.getLives() == 0) {
                    cout << endl << endl << "You ran out of lives!" << endl;
                    cout << "========================================" << endl;
                    cout << "               GAME OVER                " << endl;
                    cout << "----------------------------------------" << endl;
                    cout << "Name: " << main.getName() << endl;
                    cout << "Money at death: $" << main.getMoney() << endl;
                    cout << "Heists completed: " << main.getSuccessfulHeists() << endl;
                    cout << "Total earned from heists: " << main.getMoneyFromHeists() << endl;
                    cout << "Number of weapons purchased: " << main.getWeaponsPurchased() << endl;
                    cout << "Number of weapons sold: " << main.getWeaponsSold() << endl;
                }
                else if (main.getInventory().size() == 0) {
                    cout << endl << endl << "All weapons were seized and you were sent to prison" << endl;
                    cout << "========================================" << endl;
                    cout << "               GAME OVER                " << endl;
                    cout << "----------------------------------------" << endl;
                    cout << "Name: " << main.getName() << endl;
                    cout << "Money at death: $" << main.getMoney() << endl;
                    cout << "Heists completed: " << main.getSuccessfulHeists() << endl;
                    cout << "Total earned from heists: " << main.getMoneyFromHeists() << endl;
                    cout << "Number of weapons purchased: " << main.getWeaponsPurchased() << endl;
                    cout << "Number of weapons sold: " << main.getWeaponsSold() << endl;
                }
            }
            isBank[pos] = false;
            banks[pos] = Bank(0, 0, 0);
            while (true) {
                int i = rand() % 132;
                if (i == pos) {continue;}
                if (map[i] == '-') {
                    map[i] = 'B';
                    isBank[i] = true;
                    banks[i] = Bank((rand() % 10) + 1, (rand() % 49001) + 1000, (rand() % 5) + 1);
                    break;
                }
            }
        }
        else if (option == "3") {}
        else {
            cout << "====================================" << endl;
            cout << "INVALID INPUT, INPUT A VALID OPTION!" << endl;
            cout << "------------------------------------" << endl << endl;
            Interact(map, isBank, isArmsDealer, armsDealer, pos, main, banks);
        }
    }
    else if (isArmsDealer[pos]) {
        cout << "======================================================" << endl;
        cout << "Hello there " << main.getName() << "! I'm " << armsDealer.getName() << ", the " << armsDealer.getType() << "-end arms dealer" << endl;
        cout << "What would you like to do? (only input a valid number)" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "1. I'd like to buy a weapon" << endl;
        cout << "2. I'd like to sell a weapon" << endl;
        cout << "3. I'd like to upgrade a weapon" << endl;
        cout << "4. I'm done here, goodbye!" << endl;
        cin >> option;
        if (option == "1") {
            while (true) {
                cout << endl;
                cout << "-----------------------------------------------------------------" << endl;
                cout << "Input the ID of the gun you want to purchase, or input 0 to exit!" << endl;
                cout << "-----------------------------------------------------------------" << endl << endl;
                cout << "Available Balance: $" << main.getMoney() << endl;
                cout << "--------------------------------------------------------" << endl;
                cout << "Ok " << main.getName() << ", here's what I got to offer!" << endl;
                cout << "--------------------------------------------------------" << endl;
                cout << "ID | Name | Power | Cost" << endl;
                cout << "------------------------" << endl;
                for (int i = 0; i < armsDealer.getWeaponry().size(); i++) {
                    cout << i + 1 << " | " << armsDealer.getWeaponry()[i].getName() << " | "
                         << armsDealer.getWeaponry()[i].getPower() << " | $" << armsDealer.getWeaponry()[i].getWorth()
                         << endl;
                }
                cin >> option;
                if ((option == "1") || (option == "2") || (option == "3") || (option == "4") || (option == "5")) {
                    if (main.getMoney() >= armsDealer.getWeaponry()[stoi(option) - 1].getWorth()) {
                        if (main.getInventory().size() < 5) {
                            main.buyWeapon(armsDealer.getWeaponry()[stoi(option) - 1].getWorth());
                            main.addItemToInventory(armsDealer.getWeaponry()[stoi(option) - 1]);
                            main.addWeaponsPurchased();
                            cout << "=================" << endl;
                            cout << "Weapon purchased!" << endl;
                            cout << "-----------------" << endl << endl;
                            cout << "====================================================================" << endl;
                            cout << "Would you like to purchase more weapons? (only input a valid number)" << endl;
                            cout << "1. Yes" << endl;
                            cout << "2. No" << endl;
                            cin >> option;
                            if (option == "1") {}
                            else if (option == "2") {break;}
                            else {
                                cout << "========================================" << endl;
                                cout << "You're wasting my time, I'm out of here!" << endl;
                                cout << "----------------------------------------" << endl;
                                cout << "(You scared off the arms dealer with the wrong input)" << endl;
                                break;
                            }
                        }
                        else {
                            cout << "===========================" << endl;
                            cout << "Not enough inventory space!" << endl;
                            break;
                        }
                    }
                    else {
                        cout << "=================" << endl;
                        cout << "Not enough money!" << endl << endl;
                    }
                }
                else if (option == "0") {
                    cout << "===================" << endl;
                    cout << "Come back whenever!" << endl;
                    break;
                }
                else {
                    cout << "========================================" << endl;
                    cout << "You're wasting my time, I'm out of here!" << endl;
                    cout << "----------------------------------------" << endl;
                    cout << "(You scared off the arms dealer with the wrong input)" << endl;
                    break;
                }
            }
        }
        else if (option == "2") {
            while (true) {
                cout << endl;
                cout << "-------------------------------------------------------------" << endl;
                cout << "Input the ID of the gun you want to sell, or input 0 to exit!" << endl;
                cout << "-------------------------------------------------------------" << endl << endl;
                cout << "Available Balance: $" << main.getMoney() << endl;
                cout << "--------------------------" << endl;
                cout << "I'll buy whatever you got!" << endl;
                cout << "--------------------------" << endl;
                cout << "ID | Name | Power | Offer" << endl;
                cout << "-------------------------" << endl;
                for (int i = 0; i < main.getInventory().size(); i++) {
                    cout << i + 1 << " | " << main.getInventory()[i].getName() << " | " << main.getInventory()[i].getPower() << " | $" << main.getInventory()[i].getWorth() << endl;
                }
                cin >> option;
                if (option == "0") {
                    cout << "===================" << endl;
                    cout << "Come back whenever!" << endl;
                    break;
                }
                try {
                    if ((stoi(option) - 1) < main.getInventory().size()) {
                        if (main.getInventory().size() > 1) {
                            main.addMoney(main.getInventory()[stoi(option) - 1].getWorth());
                            main.removeWeapon(stoi(option) - 1);
                            main.addWeaponsSold();
                            cout << "============" << endl;
                            cout << "Weapon sold!" << endl;
                            cout << "------------" << endl << endl;
                            cout << "====================================================================" << endl;
                            cout << "Would you like to sell more weapons? (only input a valid number)" << endl;
                            cout << "1. Yes" << endl;
                            cout << "2. No" << endl;
                            cin >> option;
                            if (option == "1") {}
                            else if (option == "2") {break;}
                            else {
                                cout << "========================================" << endl;
                                cout << "You're wasting my time, I'm out of here!" << endl;
                                cout << "----------------------------------------" << endl;
                                cout << "(You scared off the arms dealer with the wrong input)" << endl;
                                break;
                            }
                        }
                        else {
                            cout << "=============================" << endl;
                            cout << "You can't sell your only gun!" << endl;
                            cout << "-----------------------------" << endl;
                            break;
                        }
                    }
                    else {
                        cout << "========================================" << endl;
                        cout << "You're wasting my time, I'm out of here!" << endl;
                        cout << "----------------------------------------" << endl;
                        cout << "(You scared off the arms dealer with the wrong input)" << endl;
                        break;
                    }
                }
                catch (const invalid_argument& e) {
                    cout << "========================================" << endl;
                    cout << "You're wasting my time, I'm out of here!" << endl;
                    cout << "----------------------------------------" << endl;
                    cout << "(You scared off the arms dealer with the wrong input)" << endl;
                    break;
                }
            }
        }
        else if (option == "3") {
            while (true) {
                cout << endl;
                cout << "----------------------------------------------------------------" << endl;
                cout << "Input the ID of the gun you want to upgrade, or input 0 to exit!" << endl;
                cout << "----------------------------------------------------------------" << endl << endl;
                cout << "Available Balance: $" << main.getMoney() << endl;
                cout << "---------------------------------------------------------------------------------------------" << endl;
                cout << "I can do wonders with anything!" << endl;
                cout << "It'll cost $500 to upgrade a low-tier weapon, $1000 for a mid-tier, and $5000 for a high-tier" << endl;
                cout << "-----------------" << endl;
                cout << "ID | Name | Power" << endl;
                cout << "-----------------" << endl;
                for (int i = 0; i < main.getInventory().size(); i++) {
                    cout << i + 1 << " | " << main.getInventory()[i].getName() << " | " << main.getInventory()[i].getPower() << endl;
                }
                cin >> option;
                if (option == "0") {
                    cout << "===================" << endl;
                    cout << "Come back whenever!" << endl;
                    break;
                }
                try {
                    if ((stoi(option) - 1) < main.getInventory().size()) {
                        if (main.getInventory()[stoi(option) - 1].getPower() < (main.getInventory()[stoi(option) - 1].getInitialPower() + 15)) {
                            if (main.getInventory()[stoi(option) - 1].getInitialPower() < 55) {main.buyWeapon(500);}
                            else if (main.getInventory()[stoi(option) - 1].getInitialPower() < 80) {main.buyWeapon(1000);}
                            else {main.buyWeapon(5000);}
                            main.upgradeWeapon(stoi(option) - 1);
                            cout << "================" << endl;
                            cout << "Weapon upgraded!" << endl;
                            cout << "----------------" << endl << endl;
                            cout << "====================================================================" << endl;
                            cout << "Would you like to upgrade more weapons? (only input a valid number)" << endl;
                            cout << "1. Yes" << endl;
                            cout << "2. No" << endl;
                            cin >> option;
                            if (option == "1") {}
                            else if (option == "2") {break;}
                            else {
                                cout << "========================================" << endl;
                                cout << "You're wasting my time, I'm out of here!" << endl;
                                cout << "----------------------------------------" << endl;
                                cout << "(You scared off the arms dealer with the wrong input)" << endl;
                                break;
                            }
                        }
                        else {
                            cout << "=======================" << endl;
                            cout << "Enhancements are maxed!" << endl;
                            cout << "-----------------------" << endl << endl;
                        }
                    }
                    else {
                        cout << "========================================" << endl;
                        cout << "You're wasting my time, I'm out of here!" << endl;
                        cout << "----------------------------------------" << endl;
                        cout << "(You scared off the arms dealer with the wrong input)" << endl;
                        break;
                    }
                }
                catch (const invalid_argument& e) {
                    cout << "========================================" << endl;
                    cout << "You're wasting my time, I'm out of here!" << endl;
                    cout << "----------------------------------------" << endl;
                    cout << "(You scared off the arms dealer with the wrong input)" << endl;
                    break;
                }
            }
        }
        else if (option == "4") {
            cout << "===================" << endl;
            cout << "Come back whenever!" << endl;
        }
        else {
            cout << "========================================" << endl;
            cout << "You're wasting my time, I'm out of here!" << endl;
            cout << "----------------------------------------" << endl;
            cout << "(You scared off the arms dealer with the wrong input)" << endl;
        }
    }
    else {
        cout << "====================================================" << endl;
        cout << "Nothing here! Try going to another point on the map!" << endl;
        cout << "----------------------------------------------------" << endl;
        while (true) {
            cout << "Input \"1\" to continue" << endl;
            cin >> option;
            if (option == "1") {break;}
            else {cout << "INVALID INPUT, INPUT A VALID OPTION!" << endl;}
        }
    }
}
void printPreviousGames() {
    string option;
    vector<vector<string>> stats = readStatsFromFile("previousgames.tsv");
    if (stats.empty()) {
        cout << "=======================" << endl;
        cout << "No previous games found" << endl;
        cout << "-----------------------" << endl;
        return;
    }
    cout << "==============PREVIOUS GAMES===============" << endl;
    for (int i = 0; i < stats.size(); i++) {
        cout << "Name: " << stats[i][0] << endl;
        cout << "Money at death: $" << stats[i][1]  << endl;
        cout << "Heists completed: " << stats[i][2]  << endl;
        cout << "Total earned from heists: $" << stats[i][3]  << endl;
        cout << "Number of weapons purchased: " << stats[i][4]  << endl;
        cout << "Number of weapons sold: " << stats[i][5]  << endl;
        cout << "------------------------------" << endl;
    }
    while (true) {
        cout << "Input \"1\" to continue" << endl;
        cin >> option;
        if (option == "1") {break;}
        else {cout << "INVALID INPUT, INPUT A VALID OPTION!" << endl;}
    }
}
int main() {
    string option, difficulty, name;
    char map[144];
    bool isBank[144], isArmsDealer[144];
    vector<Bank> banks;
    NPC armsDealer("","");
    int pos = 137, armsPos= -1;
    cout << "======================================================" << endl;
    cout << "              Welcome to Cyberpunk Heist!             " << endl;
    cout << "======================================================" << endl;
    do {
        cout << "Please select a difficulty (only input a valid number)" << endl;
        cout << "1. Hard" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Easy" << endl;
        cin >> difficulty;
        cin.ignore();
        if (!(difficulty == "1" || difficulty == "2" || difficulty == "3")) {
            cout << "INVALID INPUT, PLEASE INPUT A VALID DIFFICULTY!" << endl;
        }
    } while (!(difficulty == "1" || difficulty == "2" || difficulty == "3"));
    cout << "======================================================" << endl;
    cout << "Now type a name for your character: ";
    getline(cin, name);
    cout << "------------------------------------------------------" << endl << endl;
    Initialize(map, isBank, isArmsDealer, banks);
    Player main(name, stoi(difficulty));
    while ((main.getLives() > 0) && (main.getInventory().size() > 0)) {
        printMap(map);
        printStats(main);
        cout << "============================================" << endl;
        cout << "Select an option (only input a valid number)" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "1. Move" << endl;
        cout << "2. Interact" << endl;
        cout << "3. Call Arms Dealer"  << endl;
        cout << "4. View Inventory"  << endl;
        cout << "5. View Past Games"  << endl;
        cout << "6. Exit"  << endl;
        cin >> option;
        if (option == "1") {Move(map, isBank, isArmsDealer, pos);}
        else if (option == "2") {Interact(map, isBank, isArmsDealer, armsDealer, pos, main, banks);}
        else if (option == "3") {callArmsDealer(map, isArmsDealer, armsPos, pos, main, armsDealer);}
        else if (option == "4") {Inventory(main.getInventory());}
        else if (option == "5") {printPreviousGames();}
        else if (option == "6") {
            cout << "========================================" << endl;
            cout << "Thank you for playing. Have a great day!" << endl;
            break;
        }
        else {cout << "INVALID INPUT, INPUT A VALID OPTION!" << endl;}
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    }
    vector<vector<string>> stats = readStatsFromFile("previousgames.tsv");
    vector<string> currentGame;
    currentGame.push_back(main.getName());
    currentGame.push_back(to_string(main.getMoney()));
    currentGame.push_back(to_string(main.getSuccessfulHeists()));
    currentGame.push_back(to_string(main.getMoneyFromHeists()));
    currentGame.push_back(to_string(main.getWeaponsPurchased()));
    currentGame.push_back(to_string(main.getWeaponsSold()));
    stats.push_back(currentGame);
    writeStatsToFile("previousgames.tsv", stats);
    return 0;
}