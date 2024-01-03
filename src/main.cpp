#include "../include/DBManager.h"
#include <string>
#include <wx/wx.h>
#include "../include/MyDBApp.h"

using namespace std;

int main() {
    wxApp::SetInstance(new MyDBApp());
    wxTheApp->CallOnInit();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    return 0;
}
