#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "Client.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include "xlnt/xlnt.hpp"
#include <cstring>

class DBManager {
public:
    ~DBManager() { delete con; }
    DBManager(const DBManager& obj) = delete;

    static DBManager* getInstance();

    void createDB(const std::string&);
    void connect(const std::string&, const std::string&, const std::string&, const std::string&);

    void insertClientToDB(const Client&);
    std::vector<Client> searchByName(std::string);
    std::vector<Client> searchByPhone(std::string);
    std::vector<Client> searchByEmail(std::string);

private:
    static DBManager* dbPtr;
    sql::mysql::MySQL_Driver* driver {nullptr};
    sql::Connection* con {nullptr};

    DBManager() : driver{nullptr}, con{nullptr} {}

    void useDB();
    void createTable(const std::string&, sql::Statement* const);

    std::vector<Client> createClientVec(std::vector<Client>&, sql::ResultSet*);
};


//class DBManager {
//public:
//    DBManager() : driver{nullptr}, con{nullptr} {}
//    ~DBManager() { delete con; }
//
//    void executeMethod();
//    int chooseMenu();
//
//    void connect(const std::string&, const std::string&, const std::string&, const std::string&);
//    void createDB(const std::string&);
//
//    void insertNewClient();
//    void insertClientToDB(const Client&);
//    std::vector<Client> searchClient();
//    void editClient();
//    void deleteClient();
//    void importFromExcel();
//
//private:
//    sql::mysql::MySQL_Driver* driver {nullptr};
//    sql::Connection* con {nullptr};
//
//    // helper functions
//    std::vector<Client> searchByName();
//    std::vector<Client> searchByPhone();
//    std::vector<Client> searchByEmail();
//
//    void editClientName(Client&);
//    void editClientPhone(Client&);
//    void editClientEmail(Client&);
//    void editClientAddress(Client&);
//
//    std::vector<Client> createClientVec(std::vector<Client>&, sql::ResultSet*);
//};

#endif
