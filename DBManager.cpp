
#include "DBManager.h"
#include <string>
#include <iostream>

using namespace std;

void DBManager::connect(const string& host, const string& user,
                        const string& password, const string& db) {
    try {
        driver = sql::mysql::get_driver_instance();

        con = driver->connect(host, user, password);
        con->setSchema(db);
    } catch (sql::SQLException& e) {
        cout << e.what() << endl;
    }
}

void DBManager::createDB(const std::string& dbName) {
    if (con) {
        sql::Statement* stmt = con->createStatement();

        // Make a database
        string createDBQuery = "CREATE DATABASE IF NOT EXISTS " + dbName;
        stmt->execute(createDBQuery);

        createTable(dbName, stmt);

        cout << "Database " << dbName << " created!" << endl;

        delete stmt;
    }
}

void DBManager::createTable(const string& dbName, sql::Statement* const stmt) {
    string useDBQuery = "USE " + dbName;
    stmt->execute(useDBQuery);

    string createTableQuery = "CREATE TABLE clients ("
                              "ClientID     INT AUTO_INCREMENT PRIMARY KEY,"
                              "FirstName    VARCHAR(128) NOT NULL,"
                              "LastName     VARCHAR(128) NOT NULL,"
                              "PhoneNumber  VARCHAR(128),"
                              "Email        VARCHAR(128),"
                              "Address      VARCHAR(128) NOT NULL,"
                              "City         VARCHAR(128) NOT NULL,"
                              "Zipcode      VARCHAR(128) NOT NULL,"
                              "State        VARCHAR(32) NOT NULL)";
    stmt->execute(createTableQuery);
}

void DBManager::insertNewClient() {
    if (con) {
        Client tempClient = Client();
        tempClient.inputNewInfo();

        sql::Statement* stmt = con->createStatement();
        string useDBQuery = "USE MyClientDB";
        stmt->execute(useDBQuery);


        sql::PreparedStatement* pstmt = con->prepareStatement(
                "INSERT INTO clients (FirstName, LastName, PhoneNumber, Email, Address, City, Zipcode, State) "
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        pstmt->setString(1, tempClient.getLastName());
        pstmt->setString(2, tempClient.getFirstName());
        pstmt->setString(3, tempClient.getPhoneNumber());
        pstmt->setString(4, tempClient.getEmail());
        pstmt->setString(5, tempClient.getAddress());
        pstmt->setString(6, tempClient.getCity());
        pstmt->setString(7, tempClient.getZipcode());
        pstmt->setString(8, tempClient.getState());
        pstmt->execute();

        delete stmt;
        delete pstmt;

        cout << "New client " << tempClient.getLastName() << " recorded!" << endl;
    }


}

