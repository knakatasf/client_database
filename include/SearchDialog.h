#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <vector>
#include <unordered_map>
#include <cstring>
#include <wx/wx.h>
#include <wx/gbsizer.h>
#include "Client.h"
#include "DBManager.h"
#include "ResultEditDialog.h"


class SearchDialog : public wxDialog {
public:
    SearchDialog(wxWindow*, wxWindowID, const wxString&, bool=false, bool=false);

private:
    wxButton* nameButton;
    wxButton* phoneButton;
    wxButton* emailButton;

    enum {
        ID_SEARCH_NAME = wxID_HIGHEST + 1,
        ID_SEARCH_PHONE,
        ID_SEARCH_EMAIL,
    };

    std::unordered_map<int, std::string> searchTypes =
            {{ID_SEARCH_NAME, "Name"},
             {ID_SEARCH_PHONE, "Phone Number"},
             {ID_SEARCH_EMAIL, "Email"}};

    bool isEditVer = false;
    bool isDeleteVer = false;

    void OnSearch(wxCommandEvent&);
};


class SearchByDialog : public wxDialog {
public:
    SearchByDialog(wxWindow*, wxWindowID, const wxString&, const std::string&, bool=false, bool=false);

private:
    wxTextCtrl* searchCtrl;
    wxButton* searchButton;
    const int ID_SEARCH = wxID_HIGHEST + 1;
    const std::string byWhat;

    bool isEditVer = false;
    bool isDeleteVer = false;

    void OnSearch(wxCommandEvent&);
};


class SearchResultDialog : public wxDialog {
public:
    SearchResultDialog(const std::vector<Client>& response)
        : wxDialog(NULL, wxID_ANY, "Search Results", wxDefaultPosition, wxDefaultSize),
          response(response) {

        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        int index = 1;
        for (Client client : response) {
            wxStaticText* clientText = new wxStaticText(this, wxID_ANY, client.toString());
            mainSizer->Add(clientText, 0, wxALL, 5);
            index++;
        }
        SetSizerAndFit(mainSizer);
    }

private:
    std::vector<Client> response;
};

#endif
