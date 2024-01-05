#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <wx/wx.h>
#include <wx/gbsizer.h>
#include "Client.h"
#include "DBManager.h"

class InsertDialog : public wxDialog {
public:
    InsertDialog(wxWindow*, wxWindowID, const wxString&);

private:
    wxTextCtrl* fNameCtrl;
    wxTextCtrl* lNameCtrl;
    wxTextCtrl* phoneCtrl;
    wxTextCtrl* emailCtrl;
    wxTextCtrl* addressCtrl;
    wxTextCtrl* cityCtrl;
    wxTextCtrl* zipCtrl;
    wxTextCtrl* stateCtrl;
    wxButton* submitButton;

    const int ID_SUBMIT = wxID_HIGHEST + 1;

    void OnSubmit(wxCommandEvent&);
    void AddTextCtrl(wxGridBagSizer*, const wxString&, wxTextCtrl*&, int);
};


#endif