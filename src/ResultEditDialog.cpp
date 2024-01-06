#include "../include/ResultEditDialog.h"

using namespace std;

ResultEditDialog::ResultEditDialog(const std::vector<Client> &response)
    : wxDialog(NULL, wxID_ANY, "Search Results", wxDefaultPosition, wxDefaultSize),
      response(response) {

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    firstIndex = wxID_HIGHEST;
    int index = 1;
    for (Client client: response) {
        wxStaticText* clientText = new wxStaticText(this, wxID_ANY, client.toString());
        mainSizer->Add(clientText, 0, wxALL, 5);

        const int eachId = firstIndex + index;
        wxButton* editButton = new wxButton(this, eachId, "EDIT");
        mainSizer->Add(editButton, 0, wxALIGN_CENTER | wxALL, 5);
        editButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ResultEditDialog::OnEdit, this, eachId);
        index++;
    }
    SetSizerAndFit(mainSizer);
}

void ResultEditDialog::OnEdit(wxCommandEvent& event) {
    int index = event.GetId() - firstIndex - 1;
    Client target = response[index];

    string title = "Edit " + target.getLastName() + "'s data";
    EditByDialog* editByDialog = new EditByDialog(this, wxID_ANY, title, target);
    editByDialog->ShowModal();
    editByDialog->Destroy();
}

EditByDialog::EditByDialog(wxWindow* parent, wxWindowID id, const wxString& title, Client& target)
    : wxDialog(parent, id, title, wxDefaultPosition, wxSize(430, 250), wxDEFAULT_DIALOG_STYLE),
      target{target} {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    string menuLabel = "What data do you want to edit?";
    wxStaticText* menuMessage = new wxStaticText(this, wxID_ANY,menuLabel);
    wxFont font(15, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    menuMessage->SetFont(font);
    mainSizer->Add(menuMessage, 0, wxALIGN_CENTER | wxALL, 10);

    nameButton = new wxButton(this, ID_EDIT_NAME, editTypes[ID_EDIT_NAME]);
    phoneButton = new wxButton(this, ID_EDIT_PHONE, editTypes[ID_EDIT_PHONE]);
    emailButton = new wxButton(this, ID_EDIT_EMAIL, editTypes[ID_EDIT_EMAIL]);
    addressButton = new wxButton(this, ID_EDIT_ADDRESS, editTypes[ID_EDIT_ADDRESS]);
    mainSizer->Add(nameButton, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(phoneButton, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(emailButton, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(addressButton, 0, wxALIGN_CENTER | wxALL, 10);


    SetSizer(mainSizer);

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EditByDialog::OnEdit, this, ID_EDIT_NAME);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EditByDialog::OnEdit, this, ID_EDIT_PHONE);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EditByDialog::OnEdit, this, ID_EDIT_EMAIL);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EditByDialog::OnEdit, this, ID_EDIT_ADDRESS);
}

void EditByDialog::OnEdit(wxCommandEvent& event) {
    int id = event.GetId();
    string editWhat = editTypes[id];
    string title = "Edit " + editWhat + " of " + target.getLastName();

    if (editWhat == "Name") {
        EditNameDialog* editNameDialog = new EditNameDialog(this, wxID_ANY, "Edit Name", target);
        editNameDialog->ShowModal();
        editNameDialog->Destroy();
    } else if (editWhat == "Phone Number") {
        EditPhoneDialog* editPhoneDialog = new EditPhoneDialog(this, wxID_ANY, "Edit Phone", target);
        editPhoneDialog->ShowModal();
        editPhoneDialog->Destroy();
    } else if (editWhat == "Email") {
        EditEmailDialog* editEmailDialog = new EditEmailDialog(this, wxID_ANY, "Edit Email", target);
        editEmailDialog->ShowModal();
        editEmailDialog->Destroy();
    } else {
        EditAddressDialog* editAddressDialog = new EditAddressDialog(this, wxID_ANY, "Edit Address", target);
        editAddressDialog->ShowModal();
        editAddressDialog->Destroy();
    }
}

void AddTextCtrl(wxWindow* parent, wxGridBagSizer* gridSizer, const wxString& labelStr, wxTextCtrl*& textCtrl, int row) {
    wxStaticText* label = new wxStaticText(parent, wxID_ANY, labelStr,wxDefaultPosition, wxDefaultSize, 0);
    textCtrl = new wxTextCtrl(parent, wxID_ANY, wxEmptyString,wxDefaultPosition, wxDefaultSize, 0);
    textCtrl->SetMinSize(wxSize(200, -1));
    gridSizer->Add(label, wxGBPosition(row, 0),wxGBSpan(1, 1),wxALIGN_RIGHT | wxALL, 5);
    gridSizer->Add(textCtrl, wxGBPosition(row, 1), wxGBSpan(1, 1),wxEXPAND | wxALL, 5);
}

EditNameDialog::EditNameDialog(wxWindow* parent, wxWindowID id, const wxString& title, Client& target)
    : wxDialog(parent, id, title, wxDefaultPosition, wxSize(430, 230), wxDEFAULT_DIALOG_STYLE),
      target{target} {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxGridBagSizer* gridSizer = new wxGridBagSizer(3, 5);

    wxStaticText* mainText = new wxStaticText(this, wxID_ANY, "Please input client name:",
                                              wxDefaultPosition, wxDefaultSize, 0);
    wxFont font(15, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mainText->SetFont(font);
    mainSizer->Add(mainText, 0, wxALIGN_CENTER | wxALL, 10);

    AddTextCtrl(this, gridSizer, "First Name:", fNameCtrl, 1);
    AddTextCtrl(this, gridSizer, "Last Name:", lNameCtrl, 2);
    mainSizer->Add(gridSizer, 0, wxALIGN_CENTER | wxALL, 10);

    submitButton = new wxButton(this, ID_SUBMIT, "Submit");
    mainSizer->Add(submitButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EditNameDialog::OnSubmit, this, ID_SUBMIT);
}


void EditNameDialog::OnSubmit(wxCommandEvent& event) {
    wxString fName = fNameCtrl->GetValue();
    wxString lName = lNameCtrl->GetValue();

    if (!target.setFirstName(fName.ToStdString())) {
        wxMessageBox("Invalid first name.. Please only use alphabets and no whitespace.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (!target.setLastName(lName.ToStdString())) {
        wxMessageBox("Invalid last name.. Please only use alphabets and no whitespace.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }

    DBManager* dbManagerPtr = DBManager::getInstance();
    dbManagerPtr->editClientName(target);

    wxString success = "Client " + target.getLastName() + " name updated!";
    wxMessageBox(success, "Success", wxOK | wxICON_INFORMATION);

    EndModal(ID_SUBMIT);
}

EditPhoneDialog::EditPhoneDialog(wxWindow* parent, wxWindowID id, const wxString& title, Client& target)
        : wxDialog(parent, id, title, wxDefaultPosition, wxSize(430, 200), wxDEFAULT_DIALOG_STYLE),
          target{target} {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxGridBagSizer* gridSizer = new wxGridBagSizer(3, 5);

    wxStaticText* mainText = new wxStaticText(this, wxID_ANY, "Please input client phone number:",
                                              wxDefaultPosition, wxDefaultSize, 0);
    wxFont font(15, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mainText->SetFont(font);
    mainSizer->Add(mainText, 0, wxALIGN_CENTER | wxALL, 10);

    AddTextCtrl(this, gridSizer, "Phone Number:", phoneCtrl, 1);
    mainSizer->Add(gridSizer, 0, wxALIGN_CENTER | wxALL, 10);

    submitButton = new wxButton(this, ID_SUBMIT, "Submit");
    mainSizer->Add(submitButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EditPhoneDialog::OnSubmit, this, ID_SUBMIT);
}

void EditPhoneDialog::OnSubmit(wxCommandEvent& event) {
    wxString phone = phoneCtrl->GetValue();

    if (!target.setPhoneNumber(phone.ToStdString())) {
        wxMessageBox("Invalid number.. Please only numbers and dash.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }

    DBManager* dbManagerPtr = DBManager::getInstance();
    dbManagerPtr->editClientPhone(target);

    wxString success = "Client " + target.getLastName() + " phone updated!";
    wxMessageBox(success, "Success", wxOK | wxICON_INFORMATION);

    EndModal(ID_SUBMIT);
}

EditEmailDialog::EditEmailDialog(wxWindow* parent, wxWindowID id, const wxString& title, Client& target)
        : wxDialog(parent, id, title, wxDefaultPosition, wxSize(430, 200), wxDEFAULT_DIALOG_STYLE),
          target{target} {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxGridBagSizer* gridSizer = new wxGridBagSizer(3, 5);

    wxStaticText* mainText = new wxStaticText(this, wxID_ANY, "Please input client email address:",
                                              wxDefaultPosition, wxDefaultSize, 0);
    wxFont font(15, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mainText->SetFont(font);
    mainSizer->Add(mainText, 0, wxALIGN_CENTER | wxALL, 10);

    AddTextCtrl(this, gridSizer, "Email Address:", emailCtrl, 1);
    mainSizer->Add(gridSizer, 0, wxALIGN_CENTER | wxALL, 10);

    submitButton = new wxButton(this, ID_SUBMIT, "Submit");
    mainSizer->Add(submitButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EditEmailDialog::OnSubmit, this, ID_SUBMIT);
}

void EditEmailDialog::OnSubmit(wxCommandEvent& event) {
    wxString email = emailCtrl->GetValue();

    if (!target.setEmail(email.ToStdString())) {
        wxMessageBox("Invalid email.. Please use the correct format.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }

    DBManager* dbManagerPtr = DBManager::getInstance();
    dbManagerPtr->editClientEmail(target);

    wxString success = "Client " + target.getLastName() + " email updated!";
    wxMessageBox(success, "Success", wxOK | wxICON_INFORMATION);

    EndModal(ID_SUBMIT);
}

EditAddressDialog::EditAddressDialog(wxWindow* parent, wxWindowID id, const wxString& title, Client& target)
        : wxDialog(parent, id, title, wxDefaultPosition, wxSize(430, 300), wxDEFAULT_DIALOG_STYLE),
          target{target} {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxGridBagSizer* gridSizer = new wxGridBagSizer(3, 5);

    wxStaticText* mainText = new wxStaticText(this, wxID_ANY, "Please input client address:",
                                              wxDefaultPosition, wxDefaultSize, 0);
    wxFont font(15, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mainText->SetFont(font);
    mainSizer->Add(mainText, 0, wxALIGN_CENTER | wxALL, 10);

    AddTextCtrl(this, gridSizer, "Address (Street and #):", addressCtrl, 1);
    AddTextCtrl(this, gridSizer, "City:", cityCtrl, 2);
    AddTextCtrl(this, gridSizer, "Zipcode:", zipCtrl, 3);
    AddTextCtrl(this, gridSizer, "State:", stateCtrl, 4);
    mainSizer->Add(gridSizer, 0, wxALIGN_CENTER | wxALL, 10);

    submitButton = new wxButton(this, ID_SUBMIT, "Submit");
    mainSizer->Add(submitButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &EditAddressDialog::OnSubmit, this, ID_SUBMIT);
}


void EditAddressDialog::OnSubmit(wxCommandEvent& event) {
    wxString address = addressCtrl->GetValue();
    wxString city = cityCtrl->GetValue();
    wxString zipcode = zipCtrl->GetValue();
    wxString state = stateCtrl->GetValue();

    if (!target.setCity(city.ToStdString())) {
        wxMessageBox("Invalid city name.. Please only use alphabets and no whitespace.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (!target.setZipcode(zipcode.ToStdString())) {
        wxMessageBox("Invalid zipcode.. Please only use numbers and no whitespace.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (!target.setState(state.ToStdString())) {
        wxMessageBox("Invalid state name.. Please only use alphabets and no whitespace.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }
    target.setAddress(address.ToStdString());

    DBManager* dbManagerPtr = DBManager::getInstance();
    dbManagerPtr->editClientAddress(target);

    wxString success = "Client " + target.getLastName() + " address updated!";
    wxMessageBox(success, "Success", wxOK | wxICON_INFORMATION);

    EndModal(ID_SUBMIT);
}