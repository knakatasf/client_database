#include "../include/MyDBFrame.h"
#include <string>

using namespace std;

MyDBFrame::MyDBFrame(const string& host, const string& user, const string& password, const string& db,
                     const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) {

    DBManager* dbManagerPtr = DBManager::getInstance();
    dbManagerPtr->connect(host, user, password, db);

    this->SetBackgroundColour(wxColour(*wxWHITE));

    insertButton = new wxButton(this, wxID_ANY, "Insert New Client");
    searchButton = new wxButton(this, wxID_ANY, "Search Client");
    editButton = new wxButton(this, wxID_ANY, "Edit Client Data");
    deleteButton = new wxButton(this, wxID_ANY, "Delete Client Data");
    importButton = new wxButton(this, wxID_ANY, "Import from Excel");

    wxBoxSizer* vBox = new wxBoxSizer(wxVERTICAL);
    wxStaticText* menuMessage = new wxStaticText(this, wxID_ANY,
                                                 "Welcome to Client Database!\nPlease choose your choice:");

    wxFont font(16, wxDECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    menuMessage->SetFont(font);
    vBox->Add(menuMessage, 0, wxALIGN_CENTER | wxALL, 10);
    vBox->Add(insertButton, 0, wxALIGN_CENTER | wxALL, 10);
    vBox->Add(searchButton, 0, wxALIGN_CENTER | wxALL, 10);
    vBox->Add(editButton, 0, wxALIGN_CENTER | wxALL, 10);
    vBox->Add(deleteButton, 0, wxALIGN_CENTER | wxALL, 10);
    vBox->Add(importButton, 0, wxALIGN_CENTER | wxALL, 10);
    SetSizer(vBox);

    insertButton->Bind(wxEVT_BUTTON, &MyDBFrame::OnInsert, this);
//    searchButton->Bind(wxEVT_BUTTON, &MyDBFrame::OnSearch, this);
//    editButton->Bind(wxEVT_BUTTON, &MyDBFrame::OnEdit, this);
//    deleteButton->Bind(wxEVT_BUTTON, &MyDBFrame::OnDelete, this);
//    importButton->Bind(wxEVT_BUTTON, &MyDBFrame::OnImport, this);
}

void MyDBFrame::OnInsert(wxCommandEvent& event) {
    InsertDialog* insertDialog = new InsertDialog(this, wxID_ANY, "Insert New Client");
    insertDialog->ShowModal();
    insertDialog->Destroy();
}