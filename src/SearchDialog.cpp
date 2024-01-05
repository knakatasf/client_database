
#include "../include/SearchDialog.h"

using namespace std;

SearchDialog::SearchDialog(wxWindow* parent, wxWindowID id, const wxString& title)
        : wxDialog(parent, id, title, wxDefaultPosition, wxSize(430, 200), wxDEFAULT_DIALOG_STYLE) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* menuMessage = new wxStaticText(this, wxID_ANY,"What do you want to use to search for a client?");
    wxFont font(15, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    menuMessage->SetFont(font);
    mainSizer->Add(menuMessage, 0, wxALIGN_CENTER | wxALL, 10);

    nameButton = new wxButton(this, ID_SEARCH_NAME, searchTypes[ID_SEARCH_NAME]);
    phoneButton = new wxButton(this, ID_SEARCH_PHONE, searchTypes[ID_SEARCH_PHONE]);
    emailButton = new wxButton(this, ID_SEARCH_EMAIL, searchTypes[ID_SEARCH_EMAIL]);
    mainSizer->Add(nameButton, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(phoneButton, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(emailButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SearchDialog::OnSearch, this, ID_SEARCH_NAME);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SearchDialog::OnSearch, this, ID_SEARCH_PHONE);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SearchDialog::OnSearch, this, ID_SEARCH_EMAIL);
}

void SearchDialog::OnSearch(wxCommandEvent& event) {
    int id = event.GetId();
    string byWhat = searchTypes[id];
    string title = "Search by " + byWhat;
    transform(byWhat.begin(), byWhat.end(), byWhat.begin(), ::tolower);
    
    SearchByDialog* searchByDialog = new SearchByDialog(this, wxID_ANY, title, byWhat);
    searchByDialog->ShowModal();
    searchByDialog->Destroy();
}

SearchByDialog::SearchByDialog(wxWindow* parent, wxWindowID id, const wxString& title, const string& byWhat)
        : wxDialog(parent, id, title, wxDefaultPosition, wxSize(430, 180), wxDEFAULT_DIALOG_STYLE),
          byWhat{byWhat} {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxString mainLabel = "Please input " + byWhat + " of client:\n(partial " + byWhat + " is acceptable)";
    wxStaticText* mainText = new wxStaticText(this, wxID_ANY, mainLabel,
                                              wxDefaultPosition, wxDefaultSize, 0);
    wxFont font(15, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mainText->SetFont(font);
    mainSizer->Add(mainText, 0, wxALIGN_CENTER | wxALL, 10);

    searchCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString,wxDefaultPosition, wxDefaultSize, 0);
    searchCtrl->SetMinSize(wxSize(200, -1));
    mainSizer->Add(searchCtrl, 0, wxALIGN_CENTER | wxALL, 10);

    searchButton = new wxButton(this, ID_SEARCH, "SEARCH");
    mainSizer->Add(searchButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SearchByDialog::OnSearch, this, ID_SEARCH);
}

void SearchByDialog::OnSearch(wxCommandEvent& event) {
    vector<Client> response;
    wxString searchValue = searchCtrl->GetValue();

    DBManager* dbManagerPtr = DBManager::getInstance();

    if (byWhat == "name") response = dbManagerPtr->searchByName(searchValue.ToStdString());
    else if (byWhat == "phone number") response = dbManagerPtr->searchByPhone(searchValue.ToStdString());
    else if (byWhat == "email") response = dbManagerPtr->searchByEmail(searchValue.ToStdString());

    if (response.size() == 0) {
        wxString notFound = "No client with " + byWhat + " similar to " + searchValue + " found..";
        wxMessageBox(notFound, "Error", wxOK | wxICON_ERROR);
        return;
    }

    SearchResultDialog* resultFrame = new SearchResultDialog(response);
    resultFrame->ShowModal();
}