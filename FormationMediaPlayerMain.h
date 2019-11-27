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
#include <wx/choice.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)
#include <wx/mediactrl.h>
#include <memory>
#include "DancerDot.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
using json = nlohmann::json;

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
        void OnPanel2LeftDoubleClick(wxMouseEvent& event);
        void OnFormationModeSelected(wxCommandEvent& event);
        void OnTransitionModeSelected(wxCommandEvent& event);
        void OnPanel2Paint1(wxPaintEvent& event);
        void OnNewFormationSelected(wxCommandEvent& event);
        void OnChoice1Select(wxCommandEvent& event);
        void OnExportImageSelected(wxCommandEvent& event);
        void OnFileSaveSelected(wxCommandEvent& event);
        void OnSaveFormationSelected(wxCommandEvent& event);
        void OnFileLoadSelected(wxCommandEvent& event);
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
        static const long ID_CHOICE1;
        static const long idMenuQuit;
        static const long idImportMusic;
        static const long idExportImage;
        static const long idSave;
        static const long idLoad;
        static const long idMenuFormation;
        static const long idMenuTransition ;
        static const long ID_MENUITEM1;
        static const long idNewFormation;
        static const long idSaveFormation;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        json j, dd;
        wxString Formation_Name;
        int choice;
        wxPoint* draw;
        wxPoint* draw_panel1;
        wxMediaCtrl* mediactrl1;
        int ConvertToTime(wxString time);
        bool SliderDragged, loaded, mode, adding_transition;
        std::fstream file;

        std::vector<std::shared_ptr<DancerDot>> dancers;
        void DrawDot(std::shared_ptr<DancerDot>& dd);
        void NewDancer();
        void NewFormation();
        void Save();
        friend class wxMediaPlayerTimer;
        friend class DancerCreatorWindowFrame;
        friend class AddTransitionMenuFrame;
        //(*Declarations(FormationMediaPlayerFrame)
        wxSlider* Slider1;
        wxMenuItem* MenuItem8;
        wxMenuItem* MenuItem7;
        wxMenuItem* MenuItem5;
        wxMenu* Menu3;
        wxButton* Button1;
        wxMenuItem* MenuItem11;
        wxMenu* MenuItem4;
        wxPanel* Panel1;
        wxMenuItem* MenuItem10;
        wxButton* Button2;
        wxMenuItem* MenuItem3;
        wxButton* Button3;
        wxStatusBar* StatusBar1;
        wxMenuItem* MenuItem6;
        wxTextCtrl* TextCtrl2;
        wxTextCtrl* TextCtrl1;
        wxPanel* Panel2;
        wxMenuItem* MenuItem9;
        wxChoice* Choice1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // FORMATIONMEDIAPLAYERMAIN_H
