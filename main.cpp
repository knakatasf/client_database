#include "DBManager.h"
#include <string>
#include <wx/wx.h>


using namespace std;

const string host = "localhost";
const string user = "root";
const string password = "MySQL129158!";
const string db = "mysql";
const string dbName = "MyClientDB";
const string tableName = "clients";
const string excelPath = "/Users/claudio/Desktop/CS_Projects/Client_Database/ClientContactInfo.xlsx";

int main() {
    DBManager MyDB = DBManager();
    MyDB.connect(host, user, password, db);
    MyDB.executeMethod();
}
