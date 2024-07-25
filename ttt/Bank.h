using namespace std;

class Bank {
    int policeNearby = 0;
    int moneyToSteal = 0;
    int vaultStrength = 0;
public:
    Bank(int policeNearby, int moneyToSteal, int vaultStrength) {
        this->policeNearby = policeNearby;
        this->moneyToSteal = moneyToSteal;
        this->vaultStrength = vaultStrength;
    }
    int getPoliceNearby();
    int getMoneyToSteal();
    int getVaultStrength();
};
