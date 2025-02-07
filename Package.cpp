#include <string>
using namespace std;

class Package {
private:
    int serial;
    string name;
    string data;
    int sms;
    int localCallMinutes;
    int otherNetworkMinutes;
    int price;
    string validity;
public:
    Package() : serial(0), sms(0), localCallMinutes(0), otherNetworkMinutes(0), price(0) {}
    Package(int serial, const string& name, const string& data, int sms,
        int localCallMinutes, int otherNetworkMinutes, int price, const string& validity)
        : serial(serial), name(name), data(data), sms(sms),
        localCallMinutes(localCallMinutes), otherNetworkMinutes(otherNetworkMinutes),
        price(price), validity(validity) {
    }

    int getSerial() const { return serial; }
    void setSerial(int s) { serial = s; }
    string getName() const { return name; }
    void setName(const string& n) { name = n; }
    string getData() const { return data; }
    void setData(const string& d) { data = d; }
    int getSMS() const { return sms; }
    void setSMS(int s) { sms = s; }
    int getLocalCallMinutes() const { return localCallMinutes; }
    void setLocalCallMinutes(int c) { localCallMinutes = c; }
    int getOtherNetworkMinutes() const { return otherNetworkMinutes; }
    void setOtherNetworkMinutes(int onm) { otherNetworkMinutes = onm; }
    int getPrice() const { return price; }
    void setPrice(int p) { price = p; }
    string getValidity() const { return validity; }
    void setValidity(const string& v) { validity = v; }
};
