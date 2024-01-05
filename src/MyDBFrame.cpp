#include "../include/MyDBFrame.h"
#include <string>

using namespace std;

MyDBFrame::MyDBFrame(const string& host, const string& user, const string& password, const string& db, const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxPoint(100, 100), wxSize(400, 300)) {

    DBManager* dbManagerPtr = DBManager::getInstance();
    dbManagerPtr->connect(host, user, password, db);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* menuMessage = new wxStaticText(this, wxID_ANY,"Welcome to Client Database!\nPlease choose your choice:");
    wxFont font(15, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    menuMessage->SetFont(font);
    mainSizer->Add(menuMessage, 0, wxALIGN_CENTER | wxALL, 10);

    insertButton = new wxButton(this, ID_INSERT, "Insert New Client");
    searchButton = new wxButton(this, ID_SEARCH, "Search Client");
    editButton = new wxButton(this, ID_EDIT, "Edit Client Data");
    deleteButton = new wxButton(this, ID_DELETE, "Delete Client Data");
    importButton = new wxButton(this, ID_IMPORT, "Import from Excel");
    mainSizer->Add(insertButton, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(searchButton, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(editButton, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(deleteButton, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(importButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MyDBFrame::OnInsert, this, ID_INSERT);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MyDBFrame::OnSearch, this, ID_SEARCH);

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

void MyDBFrame::OnSearch(wxCommandEvent& event) {
    SearchDialog* searchDialog = new SearchDialog(this, wxID_ANY, "Search Client");
    searchDialog->ShowModal();
    searchDialog->Destroy();
}