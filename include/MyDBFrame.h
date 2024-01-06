#ifndef MYDBFRAME_H
#define MYDBFRAME_H

#include <string>
#include <wx/wx.h>
#include "DBManager.h"
#include "InsertDialog.h"
#include "SearchDialog.h"

class MyDBFrame : public wxFrame {
public:
    MyDBFrame(const std::string&, const std::string&, const std::string&, const std::string&, const wxString&);

private:
    wxButton* insertButton;
    wxButton* searchButton;
    wxButton* editButton;
    wxButton* deleteButton;
    wxButton* importButton;

    enum {
        ID_INSERT = wxID_HIGHEST + 1,
        ID_SEARCH,
        ID_EDIT,
        ID_DELETE,
        ID_IMPORT
    };

    void OnInsert(wxCommandEvent&);
    void OnSearch(wxCommandEvent&);
    void OnEdit(wxCommandEvent&);
    void OnDelete(wxCommandEvent&);
//    void OnImport(wxCommandEvent&) { dbManager.importFromExcel(); }

};

#endif
