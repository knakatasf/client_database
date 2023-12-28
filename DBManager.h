#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "Client.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/Statement.h>
#include <cppconn/resultset.h>


class DBManager {
public:
    DBManager() : driver{nullptr}, con{nullptr} {}
    ~DBManager() {delete con;}

    void connect(const std::string&, const std::string&, const std::string&, const std::string&);
    void createDB(const std::string&);

    void insertNewClient();

    void readExcel();

private:
    sql::mysql::MySQL_Driver* driver {nullptr};
    sql::Connection* con {nullptr};

    void createTable(const std::string&, sql::Statement* const);
};


#endif
