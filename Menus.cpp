#include <iostream>
using namespace std;

namespace Menus {
    void mainMenu() {
        cout << " ****************************************************************** " << endl;
        cout << "                          Sim Packages System                         " << endl;
        cout << " ****************************************************************** " << endl << endl;
        cout << " Select an Option \n" << endl;
        cout << " 1) Admin Section " << endl;
        cout << " 2) Customer Section " << endl;
        cout << " 3) Exit " << endl;
        cout << " => ";
    }
    void adminMenu() {
        cout << "Please select any option: " << endl;
        cout << "1) Add new offers " << endl;
        cout << "2) Delete offers " << endl;
        cout << "3) Update offers " << endl;
        cout << "4) Display offer list" << endl;
        cout << "5) Suggesstion centre" << endl;
        cout << "6) Exit " << endl;
        cout << "=> ";
    }
    void loginMenu() {
        cout << "------------------    MENU   ----------------------\n";
        cout << "    Welcome to User Login and Registration page    \n";
        cout << "---------------------------------------------------\n";
        cout << "Press 1 to login               " << endl;
        cout << "Press 2 to Register            " << endl;
        cout << "Press 3 to Reset Password      " << endl;
        cout << "Press 4 to exit                " << endl;
        cout << "\nplease enter your choice";
        cout << "=> ";
    }
    void customerMenu() {
        cout << "\n\nPlease select any option: " << endl;
        cout << "1) Current balance " << endl;
        cout << "2) Recharge balance " << endl;
        cout << "3) Avail offer " << endl;
        cout << "4) Customize package " << endl;
        cout << "5) Feedback " << endl;
        cout << "0) Exit" << endl;
        cout << "=> ";
    }
}
