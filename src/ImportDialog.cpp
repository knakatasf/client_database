#include "../include/ImportDialog.h"

using namespace std;

ImportDialog::ImportDialog(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxDialog(parent, id, title, wxDefaultPosition, wxSize(430, 150), wxDEFAULT_DIALOG_STYLE) {

        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* mainText = new wxStaticText(this, wxID_ANY, "Please input name of Excel file to import:",
                                                  wxDefaultPosition, wxDefaultSize, 0);
        wxFont font(15, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        mainText->SetFont(font);
        mainSizer->Add(mainText, 0, wxALIGN_CENTER | wxALL, 10);

        excelCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString,wxDefaultPosition, wxDefaultSize, 0);
        excelCtrl->SetMinSize(wxSize(200, -1));
        mainSizer->Add(excelCtrl, 0, wxALIGN_CENTER | wxALL, 10);

        importButton = new wxButton(this, ID_IMPORT, "IMPORT");
        mainSizer->Add(importButton, 0, wxALIGN_CENTER | wxALL, 10);

        SetSizer(mainSizer);

        Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ImportDialog::OnImport, this, ID_IMPORT);
}

void ImportDialog::OnImport(wxCommandEvent& event) {
    string excelPath = excelCtrl->GetValue().ToStdString();
    try {
        DBManager* dbManager = DBManager::getInstance();
        dbManager->importFromExcel(excelPath);

        wxString completed = "Succeeded in importing from Excel file!";
        wxMessageBox(completed, "Success", wxOK | wxICON_INFORMATION);
        EndModal(ID_IMPORT);

    } catch (const exception& e) {
        wxString notFound = "Couldn't find the file..";
        wxMessageBox(notFound, "Error", wxOK | wxICON_ERROR);
        return;
    }
}
