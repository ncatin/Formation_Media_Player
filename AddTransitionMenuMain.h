/***************************************************************
 * Name:      AddTransitionMenuMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2019-10-30
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef ADDTRANSITIONMENUMAIN_H
#define ADDTRANSITIONMENUMAIN_H

//(*Headers(AddTransitionMenuFrame)
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include "FormationMediaPlayerMain.h"

class AddTransitionMenuFrame: public wxFrame
{
    public:

        AddTransitionMenuFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~AddTransitionMenuFrame();

    private:

        //(*Handlers(AddTransitionMenuFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnAddPathClick(wxCommandEvent& event);
        void OnCloseClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(AddTransitionMenuFrame)
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON2;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        FormationMediaPlayerFrame* frame_parent;

        //(*Declarations(AddTransitionMenuFrame)
        wxStaticText* StaticText1;
        wxButton* Button2;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrl1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // ADDTRANSITIONMENUMAIN_H
