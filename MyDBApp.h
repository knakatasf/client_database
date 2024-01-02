
#ifndef MYDBAPP_H
#define MYDBAPP_H

#include <wx/wx.h>
#include "MyDBFrame.h"
#include "DBAppConfig.h"

#include <string>

class MyDBApp : public wxApp {
public:
    virtual bool OnInit() {
        MyDBFrame* dbFrame = new MyDBFrame(DBAppConfig::HOST, DBAppConfig::USER, DBAppConfig::PASSWORD, DBAppConfig::DB,
                                           "My Client Database", wxPoint(100, 100), wxSize(400, 200));

        dbFrame->Show(true);
        SetTopWindow(dbFrame);
        return true;
    }
};


#endif
