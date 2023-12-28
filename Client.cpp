#include "Client.h"
#include <iostream>

using namespace std;

int Client::getClientID() const { return clientID; }
string Client::getLastName() const { return lastName; }
string Client::getFirstName() const { return firstName; }
string Client::getPhoneNumber() const { return phoneNumber; }
string Client:: getEmail() const { return email; }
string Client::getAddress() const { return address; }
string Client::getCity() const { return city; }
string Client::getZipcode() const { return zipcode; }
string Client::getState() const { return state; }

void Client::inputNewInfo() {
    cout << "Please enter the following information of new client:" << endl;

    cout << "Client first name: ";
    getline(cin, firstName);
    while (!isValidName(firstName)) {
        cout << "Invalid name.. Please only use alphabets and no whitespace." << endl;
        cout << "Client first name: ";
        getline(cin, firstName);
    }

    cout << "Client last name: ";
    getline(cin, lastName);
    while (!isValidName(lastName)) {
        cout << "Invalid name.. Please only use alphabets and no whitespace." << endl;
        cout << "Client last name: ";
        getline(cin, lastName);
    }

    cout << "Client phone number (ex. 123-456-7890): ";
    getline(cin, phoneNumber);
    while (!isValidPhone(phoneNumber)) {
        cout << "Invalid number.. Please only numbers and dash." << endl;
        cout << "Client phone number (ex. 123-456-7890): ";
        getline(cin, phoneNumber);
    }

    cout << "Client email address: ";
    getline(cin, email);
    while (!isValidEmail(email)) {
        cout << "Invalid email.. Please use the correct format." << endl;
        cout << "Client email address: ";
        getline(cin, email);
    }

    cout << "Client address (street and number): ";
    getline(cin, address);

    cout << "Client city name: ";
    getline(cin, city);
    while (!isValidName(city)) {
        cout << "Invalid city name.. Please only use alphabets and no whitespace." << endl;
        cout << "Client city name: ";
        getline(cin, city);
    }

    cout << "Client zipcode: ";
    getline(cin, zipcode);
    while (!isValidZip(zipcode)) {
        cout << "Invalid zipcode.. Please only use numbers and no whitespace." << endl;
        cout << "Client zipcode: ";
        getline(cin, zipcode);
    }

    cout << "Client state name : ";
    getline(cin, state);
    while (!isValidName(state)) {
        cout << "Invalid state name.. Please only use alphabet and no whitespace." << endl;
        cout << "Client state: ";
        getline(cin, state);
    }
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