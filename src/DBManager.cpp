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

//void DBManager::executeMethod() {
//    int choice = chooseMenu();
//
//    while (choice != 6) {
//        switch (choice) {
//            case 1 : insertNewClient(); break;
//            case 2 : searchClient(); break;
//            case 3 : editClient(); break;
//            case 4 : deleteClient(); break;
//            case 5 : importFromExcel(); break;
//        }
//        choice = chooseMenu();
//    }
//    cout << "Thank you for using this program. Bye!" << endl;
//}
//
//int DBManager::chooseMenu() {
//    string input;
//    int choice;
//    cout << "Hello, welcome to MyClient DB! How can I help you?" << endl;
//    cout << "1: Insert a new client\n2: Search a client\n3: Edit client data" << endl;
//    cout << "4: Delete client data\n5: Import client data from Excel\n6: Quit the program"<< endl;
//    cout << "Enter your choice in number -> ";
//
//    while (true) {
//        getline(cin, input);
//        stringstream convert(input);
//        if (convert >> choice && choice >= 1 && choice <= 6) break;
//        cout << "Invalid entry.. Please enter a valid number -> ";
//    }
//    return choice;
//}
//
//
//void DBManager::insertNewClient() {
//    if (con) {
//        Client tempClient = Client();
//        tempClient.inputNewInfo();
//
//        useDB();
//
//        insertClientToDB(tempClient);
//    }
//
//
//}
//
//std::vector<Client> DBManager::searchClient() {
//    int choice;
//    string input;
//    cout << "What do you want to use to search for a client?" << endl;
//    cout << "1: Name\n2: Phone Number\n3: Email\n4: Quit\nPlease enter your choice in number -> ";
//    while (true) {
//        getline(cin, input);
//        stringstream convert(input);
//        if  (convert >> choice && choice >= 1 && choice <= 4) break;
//        cout << "Invalid entry.. Please enter a valid number -> ";
//    }
//
//    vector<Client> resVec;
//    switch (choice) {
//        case 1: resVec = searchByName(); break;
//        case 2: resVec = searchByPhone(); break;
//        case 3: resVec = searchByEmail(); break;
//    }
//    return resVec;
//}
//
//void DBManager::editClient() {
//    vector<Client> resVec;
//    resVec = searchClient();
//
//    Client target;
//    if (resVec.size() >= 2) {
//        int index;
//        string input;
//        cout << "Which client's data do you want to edit?" << endl;
//        cout << "Please indicate by Client Index. To quit, press 0: ";
//        while (true) {
//            getline(cin, input);
//            stringstream convert(input);
//            if  (convert >> index && index >= 0 && index <= resVec.size()) break;
//            cout << "Invalid entry.. Please enter a valid number -> ";
//        }
//        if (index == 0) return;
//        target = resVec[index-1];
//    } else if (resVec.size() == 1) target = resVec[0];
//    else return;
//
//    string input;
//    int choice;
//    target.displayClient();
//    cout << "Which data do you want to edit?" << endl;
//    cout << "1: Name\n2: Phone Number\n3: Email\n4: Address 5: Quit -> ";
//    while (true) {
//        getline(cin, input);
//        stringstream convert(input);
//        if  (convert >> choice && choice >= 1 && choice <= 5) break;
//        cout << "Invalid entry.. Please enter a valid number -> ";
//    }
//
//    if (choice == 5) return;
//
//    switch (choice) {
//        case 1: editClientName(target); break;
//        case 2: editClientPhone(target); break;
//        case 3: editClientEmail(target); break;
//        case 4: editClientAddress(target); break;
//    }
//}
//
//void DBManager::deleteClient() {
//    vector<Client> resVec;
//    resVec = searchClient();
//    Client target;
//
//    if (resVec.size() >= 2) {
//        int index;
//        string input;
//        cout << "Which client's data do you want to edit?" << endl;
//        cout << "Please indicate by Client Index. To quit, press 0: ";
//        while (true) {
//            getline(cin, input);
//            stringstream convert(input);
//            if  (convert >> index && index >= 0 && index <= resVec.size()) break;
//            cout << "Invalid entry.. Please enter a valid number -> ";
//        }
//        if (index == 0) return;
//        target = resVec[index-1];
//    } else if (resVec.size() == 1) target = resVec[0];
//    else return;
//
//    if (con) {
//        sql::PreparedStatement* pstmt = con->prepareStatement(
//                "DELETE FROM clients WHERE ClientID = ?");
//        pstmt->setInt(1, target.getClientID());
//        pstmt->execute();
//
//        delete pstmt;
//        cout << "Client " << target.getLastName() << " deleted!" << endl;
//    }
//}
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

//
//std::vector<Client> DBManager::searchByName() {
//    vector<Client> resVec;
//    if (con) {
//        string searchName;
//        cout << "Please input name of client (partial name is acceptable): ";
//        getline(cin, searchName);
//        transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
//
//        useDB();
//
//        sql::Statement* stmt = con->createStatement();
//        string searchQuery =
//                "SELECT * FROM clients WHERE LOWER(LastName) LIKE '%" + searchName
//                + "%' OR LOWER(FirstName) LIKE '%" + searchName + "%'";
//
//        sql::ResultSet* res = stmt->executeQuery(searchQuery);
//
//        if (res->rowsCount() == 0) cout << "No client with name similar to " << searchName << " found..";
//        else {
//            createClientVec(resVec, res);
//
//            cout << resVec.size() << " client(s) found." << endl;
//            int index = 1;
//            for (Client c: resVec) {
//                cout << "Client " << index << ":" << endl;
//                c.displayClient();
//                index++;
//            }
//        }
//        delete stmt;
//        delete res;
//    }
//    return resVec;
//}
//
//std::vector<Client> DBManager::searchByPhone() {
//    vector<Client> resVec;
//    if (con) {
//        string searchPhone;
//        cout << "Please input phone number of client (partial number is acceptable): ";
//        getline(cin, searchPhone);
//        transform(searchPhone.begin(), searchPhone.end(), searchPhone.begin(), ::tolower);
//
//        useDB();
//
//        sql::Statement *stmt = con->createStatement();
//        string searchQuery =
//                "SELECT * FROM clients WHERE PhoneNumber LIKE '%" + searchPhone + "%'";
//
//        sql::ResultSet *res = stmt->executeQuery(searchQuery);
//
//        if (res->rowsCount() == 0) cout << "No client with phone number similar to " << searchPhone << " found..";
//        else {
//            createClientVec(resVec, res);
//
//            cout << resVec.size() << " client(s) found." << endl;
//            int index = 1;
//            for (Client c: resVec) {
//                cout << "Client " << index << ":" << endl;
//                c.displayClient();;
//                index++;
//            }
//        }
//        delete stmt;
//        delete res;
//    }
//    return resVec;
//}
//
//std::vector<Client> DBManager::searchByEmail() {
//    vector<Client> resVec;
//    if (con) {
//        string searchEmail;
//        cout << "Please input email address of client (partial email is acceptable): ";
//        getline(cin, searchEmail);
//        transform(searchEmail.begin(), searchEmail.end(), searchEmail.begin(), ::tolower);
//
//        useDB();
//
//        sql::Statement *stmt = con->createStatement();
//        string searchQuery =
//                "SELECT * FROM clients WHERE Email LIKE '%" + searchEmail + "%'";
//
//        sql::ResultSet *res = stmt->executeQuery(searchQuery);
//
//        if (res->rowsCount() == 0) cout << "No client with email address similar to " << searchEmail << " found..";
//        else {
//            createClientVec(resVec, res);
//
//            cout << resVec.size() << " client(s) found." << endl;
//            int index = 1;
//            for (Client c: resVec) {
//                cout << "Client " << index << ":" << endl;
//                c.displayClient();;
//                index++;
//            }
//        }
//        delete stmt;
//        delete res;
//    }
//    return resVec;
//}
//
//void DBManager::editClientName(Client& target) {
//    target.inputName();
//    if (con) {
//        sql::PreparedStatement* pstmt = con->prepareStatement(
//                "UPDATE clients SET FirstName = ?, LastName = ? WHERE ClientID = ?");
//        pstmt->setString(1, target.getFirstName());
//        pstmt->setString(2, target.getLastName());
//        pstmt->setInt(3, target.getClientID());
//        pstmt->execute();
//
//        delete pstmt;
//        cout << "Client " << target.getLastName() << " updated!" << endl;
//    }
//}
//
//void DBManager::editClientPhone(Client& target) {
//    target.inputPhone();
//    if (con) {
//        sql::PreparedStatement* pstmt = con->prepareStatement(
//                "UPDATE clients SET PhoneNumber = ? WHERE ClientID = ?");
//        pstmt->setString(1, target.getPhoneNumber());
//        pstmt->setInt(2, target.getClientID());
//        pstmt->execute();
//
//        delete pstmt;
//        cout << "Client " << target.getLastName() << " updated!" << endl;
//    }
//}
//
//void DBManager::editClientEmail(Client& target) {
//    target.inputEmail();
//    if (con) {
//        sql::PreparedStatement* pstmt = con->prepareStatement(
//                "UPDATE clients SET Email = ? WHERE ClientID = ?");
//        pstmt->setString(1, target.getEmail());
//        pstmt->setInt(2, target.getClientID());
//        pstmt->execute();
//
//        delete pstmt;
//        cout << "Client " << target.getLastName() << " updated!" << endl;
//    }
//}
//
//void DBManager::editClientAddress(Client& target) {
//    target.inputAddress();
//    if (con) {
//        sql::PreparedStatement* pstmt = con->prepareStatement(
//                "UPDATE clients SET Address = ?, City = ?, Zipcode = ?, State = ? WHERE ClientID = ?");
//        pstmt->setString(1, target.getAddress());
//        pstmt->setString(2, target.getCity());
//        pstmt->setString(3, target.getZipcode());
//        pstmt->setString(4, target.getState());
//        pstmt->setInt(5, target.getClientID());
//        pstmt->execute();
//
//        delete pstmt;
//        cout << "Client " << target.getLastName() << " updated!" << endl;
//    }
//}
//
//vector<Client> DBManager::createClientVec(vector<Client>& resVec, sql::ResultSet* res) {
//    while (res->next()) {
//        Client tempClient;
//        tempClient.setClientID(res->getInt("ClientID"));
//        tempClient.setFirstName(res->getString("FirstName"));
//        tempClient.setLastName(res->getString("LastName"));
//        tempClient.setPhoneNumber(res->getString("PhoneNumber"));
//        tempClient.setEmail(res->getString("Email"));
//        tempClient.setAddress(res->getString("Address"));
//        tempClient.setCity(res->getString("City"));
//        tempClient.setZipcode(res->getString("Zipcode"));
//        tempClient.setState(res->getString("State"));
//
//        resVec.push_back(tempClient);
//    }
//    return resVec;
//}
