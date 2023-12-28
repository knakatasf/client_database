#include "DBManager.h"
#include <string>
#include <xlnt/xlnt.hpp>

using namespace std;

const string host = "localhost";
const string user = "root";
const string password = "MySQL129158!";
const string db = "mysql";

int main() {
    DBManager MyDB = DBManager();
    MyDB.connect(host, user, password, db);
    MyDB.createDB("MyClientDB");

    MyDB.insertNewClient();

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
