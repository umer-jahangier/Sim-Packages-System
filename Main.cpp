#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

#include "Package.cpp"
#include "PackageManager.cpp"
#include "FeedbackManager.cpp"
#include "AccountManager.cpp"
#include "AuthenticationManager.cpp"
#include "Menus.cpp"


void customerPage(PackageManager& pkgManager, AccountManager& accManager, const string& userNumber) {
    int option;
    int offerSerial;
    string feedback;
    int net, sms, localCalls, otherNetwork;
    int days;
    int balance = accManager.getBalance(userNumber);
    while (true) {
        Menus::customerMenu();
        cin >> option;
        cin.clear();
        cin.ignore();
        system("cls");
        if (option == 0)
            break;
        switch (option) {
        case 1:
            balance = accManager.getBalance(userNumber);
            cout << "\nYour Current Balance is: " << balance << " Rs.";
            break;
        case 2:
            accManager.rechargeBalance(userNumber, balance);
            break;
        case 3:
            pkgManager.displayPackages();
            cout << "Enter The subscription serial that you want to avail : ";
            cin >> offerSerial;
            pkgManager.calculateOffer(offerSerial, balance, userNumber);
            break;
        case 4:
            cout << "ENTER THE DATA:" << endl;
            cin >> net;
            cout << "ENTER THE SMS:" << endl;
            cin >> sms;
            cout << "ENTER THE ON-NET-MINUTES:" << endl;
            cin >> localCalls;
            cout << "ENTER THE OTHER-NETWORK:" << endl;
            cin >> otherNetwork;
            cout << "ENTER VALIDITY OF THE PACKAGE as per day:" << endl;
            cin >> days;
            pkgManager.customizeOffer(net, sms, localCalls, otherNetwork, days, balance, userNumber);
            break;
        case 5:
            cout << "please give your feedback: " << endl;
            cin.ignore();
            getline(cin, feedback);
            {
                FeedbackManager fbManager;
                fbManager.enqueueFeedback(feedback);
            }
            break;
        default:
            cout << "Invalid input!Please enter a valid input." << endl;
            break;
        }
    }
}

int main() {
    PackageManager pkgManager;
    pkgManager.loadPackagesFromFile();

    FeedbackManager fbManager;
    fbManager.loadFeedbacksFromFile();

    AccountManager accManager;
    AuthenticationManager authManager;

    int mainChoice;
    while (true) {
        cout << "\n\t    ***** Welcome to Sim Packages Application *****" << endl << endl;
        Menus::mainMenu();
        cin >> mainChoice;
        cin.clear();
        cin.ignore();
        while (mainChoice < 1 || mainChoice > 3) {
            cout << "Wrong input! Please enter valid input" << endl;
            cout << "=> ";
            cin >> mainChoice;
            cin.clear();
            cin.ignore();
        }
        system("cls");
        if (mainChoice == 1) {  // Admin Section
            while (true) {
                string pass;
                cout << "\nPlease Enter Password to Login to Admin Portal " << endl << "=> ";
                char ch;
                while ((ch = _getch()) != '\r') {  // Hide password input.
                    pass += ch;
                    cout << "*";
                }
                system("cls");
                if (pass == "0000") {
                    int option;
                    while (true) {
                        Menus::adminMenu();
                        cin >> option;
                        cin.clear();
                        cin.ignore();
                        system("cls");
                        if (option == 6)
                            break;
                        switch (option) {
                        case 1: {
                            // Add new offer.
                            ofstream outfile("Packages List.txt", ios_base::app);
                            int serial, sms, localCall, otherNetwork, price;
                            string pkgName, data, validity;
                            cout << "ENTER SERIAL NO:" << endl;
                            cin >> serial;
                            outfile << "Package Serial: " << serial << endl;
                            cout << "ENTER THE NAME:" << endl;
                            cin.ignore();
                            getline(cin, pkgName);
                            outfile << "Package Name: " << pkgName << endl;
                            cout << "ENTER THE DATA:" << endl;
                            cin >> data;
                            outfile << "Data: " << data << endl;
                            cout << "ENTER THE SMS:" << endl;
                            cin >> sms;
                            outfile << "sms: " << sms << endl;
                            cout << "ENTER THE ON-NET-MINUTES:" << endl;
                            cin >> localCall;
                            outfile << "local call minutes: " << localCall << endl;
                            cout << "ENTER THE OTHER-NETWORK:" << endl;
                            cin >> otherNetwork;
                            outfile << "other network minutes: " << otherNetwork << endl;
                            cout << "ENTER THE PRICE OF THIS PACKAGE:" << endl;
                            cin >> price;
                            outfile << "price: " << price << endl;
                            cout << "ENTER VALIDITY OF THE PACKAGE:" << endl;
                            cin.ignore();
                            getline(cin, validity);
                            outfile << "validity: " << validity << endl;
                            outfile << endl;
                            outfile.close();
                            Package newPkg(serial, pkgName, data, sms, localCall, otherNetwork, price, validity);
                            pkgManager.addPackage(newPkg);
                            break;
                        }
                        case 2:
                            pkgManager.deletePackage();
                            break;
                        case 3:
                            pkgManager.updatePackage();
                            break;
                        case 4:
                            pkgManager.displayPackages();
                            break;
                        case 5: {
                            int fbChoice;
                            cout << "feedback by customers:" << endl;
                            fbManager.displayFeedbacks();
                            cout << "Press 1 for eliminating the feedback notification: " << endl;
                            cout << " Enter 0 to exit\n";
                            cin >> fbChoice;
                            if (fbChoice == 1) {
                                fbManager.dequeueFeedback();
                                cout << endl << endl;
                            }
                            break;
                        }
                        default:
                            cout << "Wrong input. Please enter valid input \n" << endl;
                            break;
                        }
                    }
                    break;
                }
                else if (pass != "0000" && pass != "0")
                    cout << "Wrong Password... Try again or Enter 0 to exit" << endl;
                else
                    break;
            }
        }
        else if (mainChoice == 2) {  // Customer Section
            while (true) {
                int select;
                string phone, pass, key;
                Menus::loginMenu();
                cin >> select;
                cin.clear();
                cin.ignore();
                system("cls");
                if (select == 4)
                    break;
                switch (select) {
                case 1: {
                    while (true) {
                        cout << "Enter Phone No : 0200-";
                        cin >> phone;
                        cout << "Enter your password : ";
                        pass = "";
                        char ch;
                        while ((ch = _getch()) != '\r') {
                            pass += ch;
                            cout << "*";
                        }
                        cout << "\nPassword Entered: " << pass << endl;
                        if (authManager.authenticate(phone, pass)) {
                            system("cls");
                            customerPage(pkgManager, accManager, phone);
                            key = "0";
                        }
                        else {
                            cout << "\nUser or Password Not Matched\n";
                            cout << "\nEnter 1 to Re-Try or 0 to Exit=>";
                            cin >> key;
                        }
                        system("cls");
                        if (key == "0")
                            break;
                    }
                    break;
                }
                case 2: {
                    while (true) {
                        bool valid = true;
                        string tempPhone;
                        do {
                            valid = true;
                            cout << "\nEnter Phone No.: 0200-";
                            cin >> tempPhone;
                            if (tempPhone.length() != 7) {
                                cout << "Length must be 7-Digits";
                                valid = false;
                            }
                            else {
                                for (char c : tempPhone) {
                                    if (c < '0' || c > '9') {
                                        cout << "Entered Number is Not Valid";
                                        valid = false;
                                        break;
                                    }
                                }
                            }
                        } while (!valid);
                        phone = tempPhone;
                        if (authManager.checkRegistration(phone)) {
                            cout << "Enter Password: ";
                            cin >> pass;
                            ofstream file("credentials.txt", ios::app);
                            file << "Number: " << phone << endl;
                            file << "Password: " << pass << endl << endl;
                            cout << "User Creation Successfull" << endl;
                            string fileName = phone + ".txt";
                            ofstream bal(fileName.c_str());
                            bal << 50;
                            bal.close();
                            cout << "Rs.50 Reward Balance added to Your account" << endl;
                            cout << "\nEnter 1 to add new user and 0 to exit=>";
                            cin >> key;
                            if (key == "0")
                                break;
                        }
                        else
                            cout << "User Already Registered" << endl;
                    }
                    system("cls");
                    break;
                }
                case 3: {
                    string tempPhone, newPass;
                    cout << "Enter your Phone No.: 0200-";
                    cin >> tempPhone;
                    cout << "Enter New Password: ";
                    cin >> newPass;
                    bool found = authManager.resetPassword(tempPhone, newPass);
                    if (found) {
                        cout << "Password Updated Successfully" << endl;
                    }
                    else {
                        cout << "User Not Found";
                        cout << "\nEnter 1 to Re-Try or ";
                    }
                    cout << "Enter 0 to Exit=>";
                    cin >> key;
                    system("cls");
                    if (key == "0")
                        break;
                    break;
                }
                }
            }
        }
        else if (mainChoice == 3) {
            cout << "Thank You" << endl;
            return 0;
        }
    }
    return 0;
}
