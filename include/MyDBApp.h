
#ifndef MYDBAPP_H
#define MYDBAPP_H

#include <wx/wx.h>
#include "MyDBFrame.h"
#include "DBAppConfig.h"

#include <string>

// Application class: this invokes a main frame
class MyDBApp : public wxApp {
public:
    virtual bool OnInit() {
        MyDBFrame* dbFrame = new MyDBFrame(DBAppConfig::HOST, DBAppConfig::USER, DBAppConfig::PASSWORD, DBAppConfig::DB, "My Client Database");

        dbFrame->Show(true);
        SetTopWindow(dbFrame);
        return true;
    }
};


#endif
