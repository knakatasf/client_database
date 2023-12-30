#include "DBManager.h"
#include <string>

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
    // MyDB.createDB("MyClientDB");

    // MyDB.insertNewClient();
    // MyDB.searchClient();
    // MyDB.editClient();
    // MyDB.deleteClient();
    MyDB.importFromExcel(excelPath);


//    xlnt::workbook wb;
//    xlnt::worksheet ws = wb.active_sheet();
//    ws.cell("A1").value(5);
//    ws.cell("B2").value("string data");
//    ws.cell("C3").formula("=RAND()");
//    ws.merge_cells("C3:C4");
//    ws.freeze_panes("B2");
//    wb.save("example.xlsx");
//    cout << "excel" << endl;
//    return 0;
}
