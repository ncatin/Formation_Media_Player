/***************************************************************
 * Name:      FormationMediaPlayerMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2019-10-11
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef FORMATIONMEDIAPLAYERMAIN_H
#define FORMATIONMEDIAPLAYERMAIN_H

//(*Headers(FormationMediaPlayerFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)
#include <wx/mediactrl.h>
#include <memory>
#include "DancerDot.h"
class FormationMediaPlayerFrame: public wxFrame
{
    public:

        FormationMediaPlayerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~FormationMediaPlayerFrame();
        wxString* tempName;
        wxColour* tempColor;

    private:

        //(*Handlers(FormationMediaPlayerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnImportMusicSelected(wxCommandEvent& event);
        void OnPlayButtonClick(wxCommandEvent& event);
        void OnPauseButtonClick(wxCommandEvent& event);
        void OnEnterTime(wxCommandEvent& event);
        void OnSlider1CmdScrollThumbTrack(wxScrollEvent& event);
        void OnSlider1CmdScrollThumbRelease(wxScrollEvent& event);
        void OnNDButtonClick(wxCommandEvent& event);
        void OnPanel2Paint(wxPaintEvent& event);
        void OnPanel2LeftDown(wxMouseEvent& event);
        //*)

        //(*Identifiers(FormationMediaPlayerFrame)
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_SLIDER1;
        static const long ID_TEXTCTRL1;
        static const long ID_TEXTCTRL2;
        static const long ID_PANEL1;
        static const long ID_BUTTON3;
        static const long ID_PANEL2;
        static const long idMenuQuit;
        static const long idImportMusic;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)


        wxPoint* draw;
        wxMediaCtrl* mediactrl1;
        int ConvertToTime(wxString time);
        bool SliderDragged, loaded;
        std::vector<std::unique_ptr<DancerDot>> dancers;
        void DrawDot(std::unique_ptr<DancerDot>& dd);
        void NewDancer();
        friend class wxMediaPlayerTimer;
        friend class DancerCreatorWindowFrame;
        //(*Declarations(FormationMediaPlayerFrame)
        wxSlider* Slider1;
        wxButton* Button1;
        wxPanel* Panel1;
        wxButton* Button2;
        wxMenuItem* MenuItem3;
        wxButton* Button3;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrl2;
        wxTextCtrl* TextCtrl1;
        wxPanel* Panel2;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // FORMATIONMEDIAPLAYERMAIN_H
