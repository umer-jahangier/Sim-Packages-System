#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class AuthenticationManager {
public:
    bool authenticate(const string& number, const string& password) {
        ifstream file("credentials.txt");
        string num, pass, skip;
        while (getline(file, num) && getline(file, pass) && getline(file, skip)) {
            size_t pos = num.find(":");
            string fileNum = num.substr(pos + 2, 8);
            pos = pass.find(":");
            string filePass = pass.substr(pos + 2);
            filePass = filePass.substr(0, filePass.find_last_not_of(" ") + 1);
            if (fileNum == number && filePass == password) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    bool checkRegistration(const string& number) {
        ifstream file("credentials.txt");
        string num, pass, skip;
        while (getline(file, num) && getline(file, pass) && getline(file, skip)) {
            size_t pos = num.find(":");
            string fileNum = num.substr(pos + 2);
            fileNum = fileNum.substr(0, fileNum.find_last_not_of(" ") + 1);
            if (fileNum == number) {
                file.close();
                return false;
            }
        }
        file.close();
        return true;
    }
    bool resetPassword(const string& number, const string& newPassword) {
        ifstream file("credentials.txt");
        bool found = false;
        string num, pass, skip;
        ofstream out("cred_temp.txt", ios::app);
        while (getline(file, num) && getline(file, pass) && getline(file, skip)) {
            size_t pos = num.find(":");
            string fileNum = num.substr(pos + 2);
            fileNum = fileNum.substr(0, fileNum.find_last_not_of(" ") + 1);
            if (fileNum == number) {
                found = true;
                out << "Number: " << number << endl;
                out << "Password: " << newPassword << endl << endl;
            }
            else {
                out << num << endl;
                out << pass << endl << endl;
            }
        }
        file.close();
        out.close();
        remove("credentials.txt");
        rename("cred_temp.txt", "credentials.txt");
        return found;
    }
};
