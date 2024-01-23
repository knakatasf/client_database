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
    // For singleton pattern, copy constructor has to be deleted.
    DBManager(const DBManager& obj) = delete;

    static DBManager* getInstance();

    void createDB(const std::string&);
    void connect(const std::string&, const std::string&, const std::string&, const std::string&);

    void insertClientToDB(const Client&);
    std::vector<Client> searchByName(std::string);
    std::vector<Client> searchByPhone(std::string);
    std::vector<Client> searchByEmail(std::string);
    void editClientName(Client&);
    void editClientPhone(Client&);
    void editClientEmail(Client&);
    void editClientAddress(Client&);
    void deleteClient(Client&);
    void importFromExcel(std::string);


private:
    static DBManager* dbPtr;
    sql::mysql::MySQL_Driver* driver {nullptr};
    sql::Connection* con {nullptr};

    DBManager() : driver{nullptr}, con{nullptr} {}

    void useDB();
    void createTable(const std::string&, sql::Statement* const);

    std::vector<Client> createClientVec(std::vector<Client>&, sql::ResultSet*);
};

#endif
