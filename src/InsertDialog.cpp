
#include "../include/InsertDialog.h"

InsertDialog::InsertDialog(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxDialog(parent, id, title, wxDefaultPosition, wxSize(430, 430), wxDEFAULT_DIALOG_STYLE) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxGridBagSizer* gridSizer = new wxGridBagSizer(3, 5);

    wxStaticText* mainText = new wxStaticText(this, wxID_ANY, "Please input Client information:",
                                              wxDefaultPosition, wxDefaultSize, 0);
    wxFont font(15, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mainText->SetFont(font);
    mainSizer->Add(mainText, 0, wxALIGN_CENTER | wxALL, 10);

    AddTextCtrl(gridSizer, "First Name:", fNameCtrl, 1);
    AddTextCtrl(gridSizer, "Last Name:", lNameCtrl, 2);
    AddTextCtrl(gridSizer, "Phone (ex. 123-456-7890):", phoneCtrl, 3);
    AddTextCtrl(gridSizer, "Email Address:", emailCtrl, 4);
    AddTextCtrl(gridSizer, "Address (Street and #):", addressCtrl, 5);
    AddTextCtrl(gridSizer, "City:", cityCtrl, 6);
    AddTextCtrl(gridSizer, "Zipcode:", zipCtrl, 7);
    AddTextCtrl(gridSizer, "State:", stateCtrl, 8);
    mainSizer->Add(gridSizer, 0, wxALIGN_CENTER | wxALL, 10);

    submitButton = new wxButton(this, ID_SUBMIT, "Submit");
    mainSizer->Add(submitButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &InsertDialog::OnSubmit, this, ID_SUBMIT);
}

void InsertDialog::AddTextCtrl(wxGridBagSizer* gridSizer, const wxString& labelStr, wxTextCtrl*& textCtrl, int row) {
    wxStaticText* label = new wxStaticText(this, wxID_ANY, labelStr,
                                           wxDefaultPosition, wxDefaultSize, 0);
    textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                              wxDefaultPosition, wxDefaultSize, 0);
    textCtrl->SetMinSize(wxSize(200, -1));
    gridSizer->Add(label, wxGBPosition(row, 0),wxGBSpan(1, 1),
                   wxALIGN_RIGHT | wxALL, 5);
    gridSizer->Add(textCtrl, wxGBPosition(row, 1), wxGBSpan(1, 1),
                   wxEXPAND | wxALL, 5);
}

void InsertDialog::OnSubmit(wxCommandEvent& event) {
    wxString fName = fNameCtrl->GetValue();
    wxString lName = lNameCtrl->GetValue();
    wxString phone = phoneCtrl->GetValue();
    wxString email = emailCtrl->GetValue();
    wxString address = addressCtrl->GetValue();
    wxString city = cityCtrl->GetValue();
    wxString zipcode = zipCtrl->GetValue();
    wxString state = stateCtrl->GetValue();

    Client client = Client();

    if (!client.setFirstName(fName.ToStdString())) {
        wxMessageBox("Invalid first name.. Please only use alphabets and no whitespace.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (!client.setLastName(lName.ToStdString())) {
        wxMessageBox("Invalid last name.. Please only use alphabets and no whitespace.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (!client.setPhoneNumber(phone.ToStdString())) {
        wxMessageBox("Invalid phone number.. Please only use numbers and dashes.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (!client.setEmail(email.ToStdString())) {
        wxMessageBox("Invalid email address.. Please use the correct format.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (!client.setCity(city.ToStdString())) {
        wxMessageBox("Invalid city name.. Please only use alphabets and no whitespace.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (!client.setZipcode(zipcode.ToStdString())) {
        wxMessageBox("Invalid zipcode.. Please only use numbers and no whitespace.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (!client.setState(state.ToStdString())) {
        wxMessageBox("Invalid state name.. Please only use alphabet and no whitespace.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }
    client.setAddress(address.ToStdString());

    DBManager* dbManagerPtr = DBManager::getInstance();
    dbManagerPtr->insertClientToDB(client);

    wxString success = "Client " + client.getLastName() + " recorded in the database!";
    wxMessageBox(success, "Success", wxOK | wxICON_INFORMATION);

    EndModal(ID_SUBMIT);
}
