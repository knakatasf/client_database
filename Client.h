#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <regex>

class Client {
public:
    Client() {}
    Client(const int, const std::string&, const std::string&,
           const std::string&, const std::string&, const std::string&,
           const std::string&, const std::string&, const std::string&);
    ~Client() {}

    int getClientID() const { return clientID; }
    std::string getLastName() const { return lastName; }
    std::string getFirstName() const { return firstName; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getEmail() const { return email; }
    std::string getAddress() const { return address; }
    std::string getCity() const { return city; }
    std::string getZipcode() const { return zipcode; }
    std::string getState() const { return state; }

    void setClientID(const int);
    bool setLastName(const std::string&);
    bool setFirstName(const std::string&);
    bool setPhoneNumber(const std::string&);
    bool setEmail(const std::string&);
    bool setAddress(const std::string&);
    bool setCity(const std::string&);
    bool setZipcode(const std::string&);
    bool setState(const std::string&);

    void inputNewInfo();
    void inputName();
    void inputPhone();
    void inputEmail();
    void inputAddress();

    void displayClient();

private:
    int clientID = 0;
    std::string lastName = "";
    std::string firstName = "";
    std::string phoneNumber = "";
    std::string email = "";
    std::string address = "";
    std::string city = "";
    std::string zipcode = "";
    std::string state = "";

    bool isValidName(const std::string&) const;
    bool isValidPhone(const std::string&) const;
    bool isValidEmail(const std::string&) const;
    bool isValidZip(const std::string&) const;
};

#endif
