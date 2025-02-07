#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class AccountManager {
public:
    int getBalance(const string& userNumber) {
        string fileName = userNumber + ".txt";
        ifstream file(fileName.c_str());
        int balance = 0;
        file >> balance;
        file.close();
        return balance;
    }
    void updateBalance(const string& userNumber, int balance) {
        string fileName = userNumber + ".txt";
        ofstream file(fileName.c_str());
        file << balance;
        file.close();
    }
    void rechargeBalance(const string& userNumber, int& balance) {
        cout << "\nEnter amount you want to recharge: ";
        int r;
        cin >> r;
        balance += r;
        cout << "\nbalance after recharging is: " << balance << endl;
        updateBalance(userNumber, balance);
    }
};
