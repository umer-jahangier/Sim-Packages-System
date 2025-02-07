#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

/*
Note: The Package class is defined in Package.cpp.
(Make sure Package.cpp is included in main.cpp before PackageManager.cpp.
*/

// A simple node for our doubly linked list:
struct PackageNode {
    Package pkg;
    PackageNode* next;
    PackageNode* prev;
    PackageNode(const Package& p) : pkg(p), next(nullptr), prev(nullptr) {}
};

class PackageManager {
private:
    PackageNode* head;
    PackageNode* tail;
    int size;
public:
    PackageManager() : head(nullptr), tail(nullptr), size(0) {}
    ~PackageManager() {
        PackageNode* current = head;
        while (current) {
            PackageNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    void addPackage(const Package& pkg) {
        PackageNode* newNode = new PackageNode(pkg);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    void displayPackages() {
        if (!head) {
            cout << "\n\t\t\tYour List is Empty\n";
            return;
        }
        PackageNode* temp = head;
        cout << "\n\t\t\t Offers are: \n\n";
        while (temp) {
            cout << "\t\t\t  ............  " << endl;
            cout << "package serial: " << temp->pkg.getSerial() << endl;
            cout << "package name: " << temp->pkg.getName() << endl;
            cout << "data: " << temp->pkg.getData() << endl;
            cout << "sms: " << temp->pkg.getSMS() << endl;
            cout << "local call minutes: " << temp->pkg.getLocalCallMinutes() << endl;
            cout << "other network minutes: " << temp->pkg.getOtherNetworkMinutes() << endl;
            cout << "validity: " << temp->pkg.getValidity() << endl;
            cout << "price: " << temp->pkg.getPrice() << endl;
            temp = temp->next;
        }
        cout << "\n";
    }
    void updatePackage() {
        int targetSerial;
        cout << "Enter Package Serial you want to edit:" << endl;
        cin >> targetSerial;
        cin.ignore();
        PackageNode* current = head;
        bool found = false;
        PackageNode* targetNode = nullptr;
        string newName, newData, newValidity;
        int newSMS, newLocal, newOther, newPrice;
        while (current) {
            if (current->pkg.getSerial() == targetSerial) {
                found = true;
                targetNode = current;
                cout << "Enter new name:" << endl;
                getline(cin, newName);
                targetNode->pkg.setName(newName);
                cout << "Enter no of mbs: " << endl;
                getline(cin, newData);
                targetNode->pkg.setData(newData + " mbs");
                cout << "enter amount of sms: " << endl;
                cin >> newSMS;
                targetNode->pkg.setSMS(newSMS);
                cout << "enter amount of local call minutes: " << endl;
                cin >> newLocal;
                targetNode->pkg.setLocalCallMinutes(newLocal);
                cout << "enter amount of other network minutes: " << endl;
                cin >> newOther;
                targetNode->pkg.setOtherNetworkMinutes(newOther);
                cout << "enter validity of the package:" << endl;
                cin.ignore();
                getline(cin, newValidity);
                targetNode->pkg.setValidity(newValidity);
                cout << "Enter new price for this package: " << endl;
                cin >> newPrice;
                targetNode->pkg.setPrice(newPrice);
                break;
            }
            current = current->next;
        }
        if (!found) {
            cout << "No Package Found with this Serial Number, Try Again Later\n" << endl;
        }
        // Update the file "Packages List.txt"
        if (found) {
            ifstream fin("Packages List.txt");
            ofstream fout("Packages_Temp.txt");
            string line;
            bool updateBlock = false;
            int count = 0;
            while (getline(fin, line)) {
                if (line.find("Package Serial:") != string::npos) {
                    int serial;
                    sscanf(line.c_str(), "Package Serial: %d", &serial);
                    if (serial == targetSerial) {
                        updateBlock = true;
                        fout << line << endl; // keep the serial line
                        count = 0;
                        continue;
                    }
                    else {
                        updateBlock = false;
                    }
                }
                if (updateBlock && count < 7) {
                    if (line.find("Package Name:") != string::npos) {
                        line = "Package Name: " + targetNode->pkg.getName();
                        count++;
                    }
                    else if (line.find("Data:") != string::npos) {
                        line = "Data: " + targetNode->pkg.getData();
                        count++;
                    }
                    else if (line.find("sms:") != string::npos) {
                        line = "sms: " + to_string(targetNode->pkg.getSMS());
                        count++;
                    }
                    else if (line.find("local call minutes:") != string::npos) {
                        line = "local call minutes: " + to_string(targetNode->pkg.getLocalCallMinutes());
                        count++;
                    }
                    else if (line.find("other network minutes:") != string::npos) {
                        line = "other network minutes: " + to_string(targetNode->pkg.getOtherNetworkMinutes());
                        count++;
                    }
                    else if (line.find("price:") != string::npos) {
                        line = "price: " + to_string(targetNode->pkg.getPrice());
                        count++;
                    }
                    else if (line.find("validity:") != string::npos) {
                        line = "validity: " + targetNode->pkg.getValidity();
                        count++;
                    }
                }
                fout << line << endl;
            }
            fin.close();
            fout.close();
            remove("Packages List.txt");
            rename("Packages_Temp.txt", "Packages List.txt");
        }
    }
    void deletePackage() {
        if (!head) {
            cout << "List for delete is Empty" << endl;
            return;
        }
        int s;
        cout << "Enter The serial that you want to Delete : ";
        cin >> s;
        PackageNode* current = head;
        bool deleted = false;
        while (current) {
            if (current->pkg.getSerial() == s) {
                if (current == head) {
                    head = current->next;
                    if (head)
                        head->prev = nullptr;
                }
                else if (current == tail) {
                    tail = current->prev;
                    if (tail)
                        tail->next = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                cout << "\nDeleted successfully\n";
                deleted = true;
                size--;
                break;
            }
            current = current->next;
        }
        if (!deleted) {
            cout << "\n no such offer exists. \n" << endl;
        }
        // Update file "Packages List.txt" by removing the block for the deleted package.
        ifstream fin("Packages List.txt");
        ofstream fout("packages_temp.txt");
        string line;
        bool skipBlock = false;
        int count = 0;
        while (getline(fin, line)) {
            if (line.find("Package Serial:") != string::npos) {
                int serial;
                sscanf(line.c_str(), "Package Serial: %d", &serial);
                if (serial == s) {
                    skipBlock = true;
                    count = 0;
                    continue;
                }
                else {
                    skipBlock = false;
                }
            }
            if (skipBlock && count < 8) {
                count++;
                continue;
            }
            fout << line << endl;
        }
        fin.close();
        fout.close();
        remove("Packages List.txt");
        rename("packages_temp.txt", "Packages List.txt");
    }
    void calculateOffer(int offerSerial, int& balance, const string& userNumber) {
        PackageNode* temp = head;
        bool validOffer = false;
        while (temp) {
            if (temp->pkg.getSerial() == offerSerial) {
                validOffer = true;
                if (balance >= temp->pkg.getPrice()) {
                    cout << "\ncongratulations, offer availed... ";
                    cout << "\n\noffer Name  : " << temp->pkg.getName();
                    int cost = temp->pkg.getPrice();
                    balance -= cost;
                    cout << "\nRemaining balance: " << balance << endl;
                    updateBalance(userNumber, balance);
                }
                else {
                    cout << "Insufficient balance, please recharge it.." << endl;
                }
                break;
            }
            temp = temp->next;
        }
        if (!validOffer) {
            cout << "\n Invalid Subscription Serial.\n";
        }
    }
    void customizeOffer(int dataAmount, int sms, int calls, int otherNetworkMinutes,
        int validityDays, int& balance, const string& userNumber) {
        int p1 = dataAmount * 3;
        int p2 = sms * 2;
        int p3 = calls * 10;
        int p4 = calls * 20;
        int total = 0;
        if (validityDays == 1)
            total = p1 + p2 + p3 + p4;
        else if (validityDays == 7)
            total = (p1 + p2 + p3 + p4) + 70;
        else if (validityDays == 15)
            total = (p1 + p2 + p3 + p4) + 150;
        else if (validityDays == 30)
            total = (p1 + p2 + p3 + p4) + 300;
        else
            total = p1 + p2 + p3 + p4+ validityDays*10;
        cout << "This offer costs : " << total << endl;
        cout << "To subscribe Enter 1 |or| To exit Enter 0 => ";
        int subscribe;
        cin >> subscribe;
        while (subscribe < 0 || subscribe > 1) {
            cout << "Wrong Input, Press 1 to Subscribe and 0 to Exit =>";
            cin >> subscribe;
        }
        if (balance >= total && subscribe == 1) {
            cout << "\nCongratulations! Offer Subscribed Successfully." << endl;
            balance -= total;
            cout << "Current Balance: " << balance;
            updateBalance(userNumber, balance);
        }
        else if (balance < total && subscribe == 1) {
            cout << "\nInsufficient Balance... Please Recharge your Account." << endl;
        }
    }
    void loadPackagesFromFile() {
        ifstream file("Packages List.txt");
        string line;
        int serial = 0, sms = 0, localCall = 0, otherNetwork = 0, price = 0;
        string pkgName, data, validity;
        while (getline(file, line)) {
            if (line.find("Package Serial:") != string::npos) {
                serial = atoi(line.substr(line.find(":") + 2).c_str());
            }
            else if (line.find("Package Name:") != string::npos) {
                pkgName = line.substr(line.find(":") + 2);
            }
            else if (line.find("Data:") != string::npos) {
                data = line.substr(line.find(":") + 2);
            }
            else if (line.find("sms") != string::npos) {
                sms = atoi(line.substr(line.find(":") + 2).c_str());
            }
            else if (line.find("local call minutes:") != string::npos) {
                localCall = atoi(line.substr(line.find(":") + 2).c_str());
            }
            else if (line.find("other network minutes:") != string::npos) {
                otherNetwork = atoi(line.substr(line.find(":") + 2).c_str());
            }
            else if (line.find("price:") != string::npos) {
                price = atoi(line.substr(line.find(":") + 2).c_str());
            }
            else if (line.find("validity:") != string::npos) {
                validity = line.substr(line.find(":") + 2);
                Package pkg(serial, pkgName, data, sms, localCall, otherNetwork, price, validity);
                addPackage(pkg);
            }
        }
        file.close();
    }
    static void updateBalance(const string& userNumber, int balance) {
        string fileName = userNumber + ".txt";
        ofstream file(fileName.c_str());
        file << balance;
        file.close();
    }
};
