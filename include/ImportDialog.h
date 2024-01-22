#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <wx/wx.h>
#include <xlnt/xlnt.hpp>
#include <string>
#include "DBManager.h"
#include "Client.h"

class ImportDialog : public wxDialog {
public:
    ImportDialog(wxWindow*, wxWindowID, const wxString&);

private:
    wxTextCtrl* excelCtrl;
    wxButton* importButton;

    const int ID_IMPORT = wxID_HIGHEST + 1;

    void OnImport(wxCommandEvent&);
};


#endif
