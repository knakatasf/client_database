#ifndef RESULTEDITDIALOG_H
#define RESULTEDITDIALOG_H

#include <string>
#include <wx/wx.h>
#include <wx/gbsizer.h>
#include "DBManager.h"
#include "Client.h"

class ResultEditDialog : public wxDialog {
public:
    ResultEditDialog(const std::vector<Client>& response, bool=false);

private:
    std::vector<Client> response;
    bool isDelete = false;
    int firstIndex;

    void OnEdit(wxCommandEvent&);
    void OnDelete(wxCommandEvent&);
};

class EditByDialog : public wxDialog {
public:
    EditByDialog(wxWindow*, wxWindowID, const wxString&, Client&);

private:
    wxButton* nameButton;
    wxButton* phoneButton;
    wxButton* emailButton;
    wxButton* addressButton;

    enum {
        ID_EDIT_NAME = wxID_HIGHEST + 1,
        ID_EDIT_PHONE,
        ID_EDIT_EMAIL,
        ID_EDIT_ADDRESS
    };

    std::unordered_map<int, std::string> editTypes =
            {{ID_EDIT_NAME, "Name"},
             {ID_EDIT_PHONE, "Phone Number"},
             {ID_EDIT_EMAIL, "Email"},
             {ID_EDIT_ADDRESS, "Address"}};

    Client target;

    void OnEdit(wxCommandEvent&);
};

void AddTextCtrl(wxWindow*, wxGridBagSizer*, const wxString&, wxTextCtrl*&, int);

class EditNameDialog : public wxDialog {
public:
    EditNameDialog(wxWindow*, wxWindowID, const wxString&, Client&);

private:
    wxTextCtrl* fNameCtrl;
    wxTextCtrl* lNameCtrl;
    wxButton* submitButton;

    const int ID_SUBMIT = wxID_HIGHEST + 1;

    Client target;

    void OnSubmit(wxCommandEvent&);
};

class EditPhoneDialog : public wxDialog {
public:
    EditPhoneDialog(wxWindow*, wxWindowID, const wxString&, Client&);

private:
    wxTextCtrl* phoneCtrl;
    wxButton* submitButton;

    const int ID_SUBMIT = wxID_HIGHEST + 1;

    Client target;

    void OnSubmit(wxCommandEvent&);
};

class EditEmailDialog : public wxDialog {
public:
    EditEmailDialog(wxWindow*, wxWindowID, const wxString&, Client&);

private:
    wxTextCtrl* emailCtrl;
    wxButton* submitButton;

    const int ID_SUBMIT = wxID_HIGHEST + 1;

    Client target;

    void OnSubmit(wxCommandEvent&);
};

class EditAddressDialog : public wxDialog {
public:
    EditAddressDialog(wxWindow*, wxWindowID, const wxString&, Client&);

private:
    wxTextCtrl* addressCtrl;
    wxTextCtrl* cityCtrl;
    wxTextCtrl* zipCtrl;
    wxTextCtrl* stateCtrl;
    wxButton* submitButton;

    const int ID_SUBMIT = wxID_HIGHEST + 1;

    Client target;

    void OnSubmit(wxCommandEvent&);
};

#endif
