#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <regex>

class Client {
public:
    Client() {}
    ~Client() {}

    int getClientID() const;
    std::string getLastName() const;
    std::string getFirstName() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    std::string getAddress() const;
    std::string getCity() const;
    std::string getZipcode() const;
    std::string getState() const;


    void inputNewInfo();

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
