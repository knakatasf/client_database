#include "Client.h"
#include <iostream>

using namespace std;

Client::Client(const int id, const string& fname, const string& lname,
       const string& number, const string& email, const string& address,
       const string& city, const string& zipcode, const string& state) {
    setClientID(id);
    setFirstName(fname);
    setLastName(lname);
    setPhoneNumber(number);
    setEmail(email);
    setAddress(address);
    setCity(city);
    setZipcode(zipcode);
    setState(state);
}

void Client::setClientID(const int id) { clientID = id; }

bool Client::setFirstName(const std::string& name) {
    if (isValidName(name)) {
        firstName = name;
        return true;
    }
    return false;
}

bool Client::setLastName(const std::string& name) {
    if (isValidName(name)) {
        lastName = name;
        return true;
    }
    return false;
}
bool Client::setPhoneNumber(const std::string& number) {
    if (isValidPhone(number)) {
        phoneNumber = number;
        return true;
    }
    return false;
}

bool Client::setEmail(const std::string& email) {
    if (isValidEmail(email)) {
        this->email = email;
        return true;
    }
    return false;
}

bool Client::setAddress(const std::string& address) {
    this->address = address;
    return true;
}

bool Client::setCity(const std::string& city) {
    if (isValidName(city)) {
        this->city = city;
        return true;
    }
    return false;
}

bool Client::setZipcode(const std::string& zipcode) {
    if (isValidZip(zipcode)) {
        this->zipcode = zipcode;
        return true;
    }
    return false;
}

bool Client::setState(const std::string& state) {
    if (isValidName(state)) {
        this->state = state;
        return true;
    }
    return false;
}

void Client::inputNewInfo() {
    cout << "Please enter the following information of new client:" << endl;

    inputName();
    inputPhone();
    inputEmail();
    inputAddress();
}

void Client::inputName() {
    string fName;
    cout << "Client first name: ";
    getline(cin, fName);
    while (!setFirstName(fName)) {
        cout << "Invalid name.. Please only use alphabets and no whitespace." << endl;
        cout << "Client first name: ";
        getline(cin, fName);
    }

    string lName;
    cout << "Client last name: ";
    getline(cin, lName);
    while (!setLastName(lName)) {
        cout << "Invalid name.. Please only use alphabets and no whitespace." << endl;
        cout << "Client last name: ";
        getline(cin, lName);
    }
}

void Client::inputPhone() {
    string pNum;
    cout << "Client phone number (ex. 123-456-7890): ";
    getline(cin, pNum);
    while (!setPhoneNumber(pNum)) {
        cout << "Invalid number.. Please only numbers and dash." << endl;
        cout << "Client phone number (ex. 123-456-7890): ";
        getline(cin, pNum);
    }
}

void Client::inputEmail() {
    string email;
    cout << "Client email address: ";
    getline(cin, email);
    while (!setEmail(email)) {
        cout << "Invalid email.. Please use the correct format." << endl;
        cout << "Client email address: ";
        getline(cin, email);
    }
}

void Client::inputAddress() {
    string address;
    cout << "Client address (street and number): ";
    getline(cin, address);
    setAddress(address);

    string city;
    cout << "Client city name: ";
    getline(cin, city);
    while (!setCity(city)) {
        cout << "Invalid city name.. Please only use alphabets and no whitespace." << endl;
        cout << "Client city name: ";
        getline(cin, city);
    }

    string zipcode;
    cout << "Client zipcode: ";
    getline(cin, zipcode);
    while (!setZipcode(zipcode)) {
        cout << "Invalid zipcode.. Please only use numbers and no whitespace." << endl;
        cout << "Client zipcode: ";
        getline(cin, zipcode);
    }

    string state;
    cout << "Client state name : ";
    getline(cin, state);
    while (!setState(state)) {
        cout << "Invalid state name.. Please only use alphabet and no whitespace." << endl;
        cout << "Client state: ";
        getline(cin, state);
    }
}

void Client::displayClient() {
    cout << "\nName: " << getLastName() << ", " << getFirstName() << endl;
    cout << "Phone: " << getPhoneNumber() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Address: " << getAddress() << ", " << getCity() << ", " << getState() << " " << getZipcode() << endl;
    cout << endl;
}

bool Client::isValidName(const string& name) const {
    for (const char c: name) {
        if (!isalpha(c)) return false;
    }
    return true;
}

bool Client::isValidPhone(const string& number) const {
    const regex phonePat ("\\d+-\\d+-\\d+");
    return regex_match(number, phonePat);
}

bool Client::isValidEmail(const std::string& email) const {
    const regex emailPat ("\\w+@\\w+\\.\\w+");
    return regex_match(email, emailPat);
}

bool Client::isValidZip(const std::string& zip) const {
    for (const char c: zip) {
        if (!isdigit(c)) return false;
    }
    return true;
}