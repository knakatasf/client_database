
#include "../include/InsertDialog.h"

InsertDialog::InsertDialog(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxDialog(parent, id, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* fNameSizer = new wxBoxSizer(wxHORIZONTAL);
    fNameSizer->Add(new wxStaticText(this, wxID_ANY, "First Name:"),
                    0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    fNameCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    fNameSizer->Add(fNameCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(fNameSizer, 0, wxEXPAND);
    fNameCtrl->SetFocus();

    wxBoxSizer* lNameSizer = new wxBoxSizer(wxHORIZONTAL);
    lNameSizer->Add(new wxStaticText(this, wxID_ANY, "Last Name:"),
                    0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    lNameCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    lNameSizer->Add(lNameCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(lNameSizer, 0, wxEXPAND);

    wxBoxSizer* phoneSizer = new wxBoxSizer(wxHORIZONTAL);
    phoneSizer->Add(new wxStaticText(this, wxID_ANY, "Phone Number:"),
                    0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    phoneCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    phoneSizer->Add(phoneCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(phoneSizer, 0, wxEXPAND);

    wxBoxSizer* emailSizer = new wxBoxSizer(wxHORIZONTAL);
    emailSizer->Add(new wxStaticText(this, wxID_ANY, "Email:"),
                    0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    emailCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    emailSizer->Add(emailCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(emailSizer, 0, wxEXPAND);

    wxBoxSizer* addressSizer = new wxBoxSizer(wxHORIZONTAL);
    addressSizer->Add(new wxStaticText(this, wxID_ANY, "Address:"),
                    0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    addressCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    addressSizer->Add(addressCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(addressSizer, 0, wxEXPAND);

    wxBoxSizer* citySizer = new wxBoxSizer(wxHORIZONTAL);
    citySizer->Add(new wxStaticText(this, wxID_ANY, "City:"),
                      0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    cityCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    citySizer->Add(cityCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(citySizer, 0, wxEXPAND);

    wxBoxSizer* zipSizer = new wxBoxSizer(wxHORIZONTAL);
    zipSizer->Add(new wxStaticText(this, wxID_ANY, "Zipcode:"),
                   0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    zipCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    zipSizer->Add(zipCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(zipSizer, 0, wxEXPAND);

    wxBoxSizer* stateSizer = new wxBoxSizer(wxHORIZONTAL);
    stateSizer->Add(new wxStaticText(this, wxID_ANY, "State:"),
                   0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    stateCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    stateSizer->Add(stateCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(stateSizer, 0, wxEXPAND);

    submitButton = new wxButton(this, ID_SUBMIT, "Submit");
    mainSizer->Add(submitButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizerAndFit(mainSizer);

    Bind(wxEVT_BUTTON, &InsertDialog::OnSubmit, this, ID_SUBMIT);
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
        wxMessageBox("Invalid name.. Please only use alphabets and no whitespace.",
                     "Error", wxOK | wxICON_ERROR);
        return;
    }

    EndModal(ID_SUBMIT);
}
