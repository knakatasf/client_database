#include "../include/DBManager.h"

using namespace std;

DBManager* DBManager::dbPtr = nullptr;

DBManager* DBManager::getInstance() {
    if (dbPtr == nullptr) {
        dbPtr = new DBManager();
        return dbPtr;
    } else return dbPtr;
}

void DBManager::createDB(const std::string& dbName) {
    if (con) {
        sql::Statement* stmt = con->createStatement();
        string createDBQuery = "CREATE DATABASE IF NOT EXISTS " + dbName;
        stmt->execute(createDBQuery);

        createTable(dbName, stmt);

        cout << "Database " << dbName << " created!" << endl;
        delete stmt;
    }
}

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

void DBManager::insertClientToDB(const Client& tempClient) {
    if (con) {
        useDB();

        sql::PreparedStatement* pstmt = con->prepareStatement(
                "INSERT INTO clients (FirstName, LastName, PhoneNumber, Email, Address, City, Zipcode, State) "
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        pstmt->setString(1, tempClient.getFirstName());
        pstmt->setString(2, tempClient.getLastName());
        pstmt->setString(3, tempClient.getPhoneNumber());
        pstmt->setString(4, tempClient.getEmail());
        pstmt->setString(5, tempClient.getAddress());
        pstmt->setString(6, tempClient.getCity());
        pstmt->setString(7, tempClient.getZipcode());
        pstmt->setString(8, tempClient.getState());
        pstmt->execute();

        delete pstmt;
    }
}

std::vector<Client> DBManager::searchByName(string searchName) {
    vector<Client> response;
    if (con) {
        useDB();

        transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

        sql::Statement* stmt = con->createStatement();
        string searchQuery =
                "SELECT * FROM clients WHERE LOWER(LastName) LIKE '%" + searchName
                + "%' OR LOWER(FirstName) LIKE '%" + searchName + "%'";
        sql::ResultSet* res = stmt->executeQuery(searchQuery);

        if (res->rowsCount() != 0) createClientVec(response, res);

        delete stmt;
        delete res;
    }
    return response;
}

std::vector<Client> DBManager::searchByPhone(string searchPhone) {
    vector<Client> response;
    if (con) {
        useDB();

        sql::Statement *stmt = con->createStatement();
        string searchQuery =
                "SELECT * FROM clients WHERE PhoneNumber LIKE '%" + searchPhone + "%'";
        sql::ResultSet *res = stmt->executeQuery(searchQuery);

        if (res->rowsCount() != 0) createClientVec(response, res);

        delete stmt;
        delete res;
    }
    return response;
}

std::vector<Client> DBManager::searchByEmail(string searchEmail) {
    vector<Client> response;
    if (con) {
        useDB();

        sql::Statement *stmt = con->createStatement();
        string searchQuery =
                "SELECT * FROM clients WHERE Email LIKE '%" + searchEmail + "%'";
        sql::ResultSet *res = stmt->executeQuery(searchQuery);

        if (res->rowsCount() != 0) createClientVec(response, res);

        delete stmt;
        delete res;
    }
    return response;
}

void DBManager::editClientName(Client& target) {
    if (con) {
        sql::PreparedStatement* pstmt = con->prepareStatement(
                "UPDATE clients SET FirstName = ?, LastName = ? WHERE ClientID = ?");
        pstmt->setString(1, target.getFirstName());
        pstmt->setString(2, target.getLastName());
        pstmt->setInt(3, target.getClientID());
        pstmt->execute();

        delete pstmt;
    }
}

void DBManager::editClientPhone(Client& target) {
    if (con) {
        sql::PreparedStatement* pstmt = con->prepareStatement(
                "UPDATE clients SET PhoneNumber = ? WHERE ClientID = ?");
        pstmt->setString(1, target.getPhoneNumber());
        pstmt->setInt(2, target.getClientID());
        pstmt->execute();

        delete pstmt;
    }
}

void DBManager::editClientEmail(Client& target) {
    if (con) {
        sql::PreparedStatement* pstmt = con->prepareStatement(
                "UPDATE clients SET Email = ? WHERE ClientID = ?");
        pstmt->setString(1, target.getEmail());
        pstmt->setInt(2, target.getClientID());
        pstmt->execute();

        delete pstmt;
        cout << "Client " << target.getLastName() << " updated!" << endl;
    }
}

void DBManager::editClientAddress(Client& target) {
    if (con) {
        sql::PreparedStatement* pstmt = con->prepareStatement(
                "UPDATE clients SET Address = ?, City = ?, Zipcode = ?, State = ? WHERE ClientID = ?");
        pstmt->setString(1, target.getAddress());
        pstmt->setString(2, target.getCity());
        pstmt->setString(3, target.getZipcode());
        pstmt->setString(4, target.getState());
        pstmt->setInt(5, target.getClientID());
        pstmt->execute();

        delete pstmt;
        cout << "Client " << target.getLastName() << " updated!" << endl;
    }
}

void DBManager::deleteClient(Client& target) {
    if (con) {
        sql::PreparedStatement* pstmt = con->prepareStatement(
                "DELETE FROM clients WHERE ClientID = ?");
        pstmt->setInt(1, target.getClientID());
        pstmt->execute();

        delete pstmt;
    }
}

void DBManager::useDB() {
    if (con) {
        sql::Statement* useStmt = con->createStatement();
        string useDBQuery = "USE MyClientDB";
        useStmt->execute(useDBQuery);
        delete useStmt;
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

    // createDB will delete stmt pointer.
}

vector<Client> DBManager::createClientVec(vector<Client>& resVec, sql::ResultSet* res) {
    while (res->next()) {
        Client tempClient;
        tempClient.setClientID(res->getInt("ClientID"));
        tempClient.setFirstName(res->getString("FirstName"));
        tempClient.setLastName(res->getString("LastName"));
        tempClient.setPhoneNumber(res->getString("PhoneNumber"));
        tempClient.setEmail(res->getString("Email"));
        tempClient.setAddress(res->getString("Address"));
        tempClient.setCity(res->getString("City"));
        tempClient.setZipcode(res->getString("Zipcode"));
        tempClient.setState(res->getString("State"));

        resVec.push_back(tempClient);
    }
    return resVec;
}


//
//void DBManager::importFromExcel() {
//    cout << "Inside the member function" << endl;
//    string excelPath;
//    cout << "Please input the excel file path: ";
//    getline(cin, excelPath);
//
//    try {
//        xlnt::workbook wb;
//        wb.load(excelPath);
//        auto ws = wb.active_sheet();
//
//        cout << "Worksheet loaded" << endl;
//
//        vector<Client> clientVec;
//        auto rows = ws.rows(false);
//        for (auto rowIter = next(rows.begin()); rowIter != rows.end(); ++rowIter) {
//            auto row = *rowIter;
//            Client client;
//
//            cout << "Inside the for loop" << endl;
//
//            string name = row[0].to_string();
//            int pos = name.find(", ");
//            string lName = name.substr(0, pos);
//            client.setLastName(lName);
//            string fName = name.substr(pos + 2, name.length());
//            client.setFirstName(fName);
//
//            client.setPhoneNumber(row[1].to_string());
//            client.setEmail(row[2].to_string());
//            client.setAddress(row[3].to_string());
//            client.setCity(row[4].to_string());
//            client.setZipcode(row[5].to_string());
//            client.setState(row[6].to_string());
//
//            clientVec.push_back(client);
//        }
//        for (Client client : clientVec) {
//            insertClientToDB(client);
//        }
//    } catch (const exception& e) {
//        cerr << "Error: " << e.what() << endl;
//    }
//}
//
