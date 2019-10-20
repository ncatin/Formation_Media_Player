/***************************************************************
 * Name:      DancerCreatorWindowMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2019-10-13
 * Copyright:  ()
 * License:
 **************************************************************/

#include "DancerCreatorWindowMain.h"
#include <wx/msgdlg.h>
#include <memory>
#include <vector>
//(*InternalHeaders(DancerCreatorWindowFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo2(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(DancerCreatorWindowFrame)
const long DancerCreatorWindowFrame::ID_STATICTEXT1 = wxNewId();
const long DancerCreatorWindowFrame::ID_TEXTCTRL1 = wxNewId();
const long DancerCreatorWindowFrame::ID_COLOURPICKERCTRL1 = wxNewId();
const long DancerCreatorWindowFrame::ID_BUTTON1 = wxNewId();
const long DancerCreatorWindowFrame::ID_STATICTEXT2 = wxNewId();
const long DancerCreatorWindowFrame::idMenuQuit = wxNewId();
const long DancerCreatorWindowFrame::idMenuAbout = wxNewId();
const long DancerCreatorWindowFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DancerCreatorWindowFrame,wxFrame)
    //(*EventTable(DancerCreatorWindowFrame)
    //*)
END_EVENT_TABLE()

DancerCreatorWindowFrame::DancerCreatorWindowFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(DancerCreatorWindowFrame)
    wxMenuItem* MenuItem2;
    wxGridBagSizer* GridBagSizer1;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    frame_parent = (FormationMediaPlayerFrame *)parent;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    GridBagSizer1 = new wxGridBagSizer(0, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    GridBagSizer1->Add(StaticText1, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    GridBagSizer1->Add(TextCtrl1, wxGBPosition(0, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ColourPickerCtrl1 = new wxColourPickerCtrl(this, ID_COLOURPICKERCTRL1, wxColour(0,0,0), wxDefaultPosition, wxSize(51,23), 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL1"));
    GridBagSizer1->Add(ColourPickerCtrl1, wxGBPosition(1, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(this, ID_BUTTON1, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    GridBagSizer1->Add(Button1, wxGBPosition(2, 1), wxGBSpan(1, 2), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Color"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    GridBagSizer1->Add(StaticText2, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(GridBagSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    GridBagSizer1->Fit(this);
    GridBagSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DancerCreatorWindowFrame::OnOKClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DancerCreatorWindowFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DancerCreatorWindowFrame::OnAbout);
    //*)
}

DancerCreatorWindowFrame::~DancerCreatorWindowFrame()
{
    //(*Destroy(DancerCreatorWindowFrame)
    //*)
}

void DancerCreatorWindowFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DancerCreatorWindowFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo2(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void DancerCreatorWindowFrame::OnOKClick(wxCommandEvent& event)
{
    *frame_parent->tempName = TextCtrl1->GetLineText(0);
    *frame_parent->tempColor = ColourPickerCtrl1->GetColour();
    frame_parent->NewDancer();
    this->Destroy();
}
