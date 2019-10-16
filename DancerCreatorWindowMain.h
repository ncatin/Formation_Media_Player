/***************************************************************
 * Name:      DancerCreatorWindowMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2019-10-13
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef DANCERCREATORWINDOWMAIN_H
#define DANCERCREATORWINDOWMAIN_H

//(*Headers(DancerCreatorWindowFrame)
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/clrpicker.h>
#include <wx/statusbr.h>
//*)

#include <memory>
#include <vector>
#include "FormationMediaPlayerMain.h"



class DancerCreatorWindowFrame: public wxFrame
{


    public:

        DancerCreatorWindowFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~DancerCreatorWindowFrame();

    private:

        //(*Handlers(DancerCreatorWindowFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOKClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(DancerCreatorWindowFrame)
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_COLOURPICKERCTRL1;
        static const long ID_BUTTON1;
        static const long ID_STATICTEXT2;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        FormationMediaPlayerFrame* frame_parent;

        //(*Declarations(DancerCreatorWindowFrame)
        wxStaticText* StaticText2;
        wxButton* Button1;
        wxStaticText* StaticText1;
        wxColourPickerCtrl* ColourPickerCtrl1;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrl1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // DANCERCREATORWINDOWMAIN_H
