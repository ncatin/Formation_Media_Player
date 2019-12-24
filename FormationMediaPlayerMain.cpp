/***************************************************************
 * Name:      FormationMediaPlayerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2019-10-11
 * Copyright:  ()
 * License:
 **************************************************************/

#include "FormationMediaPlayerMain.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/mediactrl.h>
#include "wxMediaPlayerTimer.h"
#include <memory>
#include "DancerCreatorWindowMain.h"
#include "AddTransitionMenuMain.h"
#include <wx/dcclient.h>
#include <wx/dc.h>
#include <wx/dcmemory.h>
#include <wx/dragimag.h>
#include <wx/generic/dragimgg.h>
#include <wx/utils.h>
#include <wx/dcscreen.h>
#include "json.hpp"
//(*InternalHeaders(FormationMediaPlayerFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#define FORMATION_MODE 0
#define TRANSITION_MODE 1

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
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

//(*IdInit(FormationMediaPlayerFrame)
const long FormationMediaPlayerFrame::ID_BUTTON1 = wxNewId();
const long FormationMediaPlayerFrame::ID_BUTTON2 = wxNewId();
const long FormationMediaPlayerFrame::ID_SLIDER1 = wxNewId();
const long FormationMediaPlayerFrame::ID_TEXTCTRL1 = wxNewId();
const long FormationMediaPlayerFrame::ID_TEXTCTRL2 = wxNewId();
const long FormationMediaPlayerFrame::ID_PANEL1 = wxNewId();
const long FormationMediaPlayerFrame::ID_BUTTON3 = wxNewId();
const long FormationMediaPlayerFrame::ID_BITMAPCOMBOBOX1 = wxNewId();
const long FormationMediaPlayerFrame::ID_CHOICE1 = wxNewId();
const long FormationMediaPlayerFrame::ID_BUTTON4 = wxNewId();
const long FormationMediaPlayerFrame::idMenuQuit = wxNewId();
const long FormationMediaPlayerFrame::idImportMusic = wxNewId();
const long FormationMediaPlayerFrame::idExportImage = wxNewId();
const long FormationMediaPlayerFrame::idSave = wxNewId();
const long FormationMediaPlayerFrame::idLoad = wxNewId();
const long FormationMediaPlayerFrame::idMenuFormation = wxNewId();
const long FormationMediaPlayerFrame::idMenuTransition  = wxNewId();
const long FormationMediaPlayerFrame::ID_MENUITEM1 = wxNewId();
const long FormationMediaPlayerFrame::idNewFormation = wxNewId();
const long FormationMediaPlayerFrame::idSaveFormation = wxNewId();
const long FormationMediaPlayerFrame::idMenuAbout = wxNewId();
const long FormationMediaPlayerFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FormationMediaPlayerFrame,wxFrame)
    //(*EventTable(FormationMediaPlayerFrame)
    //*)
END_EVENT_TABLE()


FormationMediaPlayerFrame::FormationMediaPlayerFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(FormationMediaPlayerFrame)
    wxMenuItem* MenuItem2;
    wxGridBagSizer* GridBagSizer1;
    wxGridBagSizer* GridBagSizer2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    mediactrl1  =  new wxMediaCtrl();

    mediactrl1->Create(this, wxID_ANY, wxEmptyString , wxDefaultPosition, wxDefaultSize, 0);

    wxMediaPlayerTimer* timer = new wxMediaPlayerTimer(this);
    timer->Start(500);

    SliderDragged = false;

    loaded = false;

    draw = new wxPoint(30,30);

    draw_panel1 = new wxPoint(0,0);

    choice = 0;

    tempName = new wxString();

    tempColor = new wxColour();

    //Panel2->SetScrollbar(wxVERTICAL, 0, 16, 50);
    FlexGridSizer1 = new wxFlexGridSizer(2, 6, 4, 1);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(1);
    GridBagSizer1 = new wxGridBagSizer(1, 1);
    GridBagSizer1->AddGrowableCol(0);
    GridBagSizer1->AddGrowableRow(0);
    Button1 = new wxButton(this, ID_BUTTON1, _("Play"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    GridBagSizer1->Add(Button1, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    Button2 = new wxButton(this, ID_BUTTON2, _("Pause"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    GridBagSizer1->Add(Button2, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    Slider1 = new wxSlider(this, ID_SLIDER1, 0, 0, 100, wxDefaultPosition, wxSize(239,24), 0, wxDefaultValidator, _T("ID_SLIDER1"));
    GridBagSizer1->Add(Slider1, wxGBPosition(2, 2), wxDefaultSpan, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("Filename"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl1->SetEditable(false);
    GridBagSizer1->Add(TextCtrl1, wxGBPosition(2, 3), wxDefaultSpan, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("Time"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    GridBagSizer1->Add(TextCtrl2, wxGBPosition(2, 4), wxDefaultSpan, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(894,590), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    GridBagSizer1->Add(Panel1, wxGBPosition(0, 0), wxGBSpan(2, 5), wxALL|wxEXPAND, 5);
    GridBagSizer2 = new wxGridBagSizer(0, 0);
    Button3 = new wxButton(this, ID_BUTTON3, _("New Dancer"), wxDefaultPosition, wxSize(111,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    GridBagSizer2->Add(Button3, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapComboBox1 = new wxBitmapComboBox(this, ID_BITMAPCOMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY, wxDefaultValidator, _T("ID_BITMAPCOMBOBOX1"));
    BitmapComboBox1->SetExtraStyle( BitmapComboBox1->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
    GridBagSizer2->Add(BitmapComboBox1, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice1 = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->SetHelpText(_("Formations"));
    GridBagSizer2->Add(Choice1, wxGBPosition(7, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button4 = new wxButton(this, ID_BUTTON4, _("Add Dancer"), wxDefaultPosition, wxSize(111,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    GridBagSizer2->Add(Button4, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridBagSizer1->Add(GridBagSizer2, wxGBPosition(0, 5), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(GridBagSizer1, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuItem3 = new wxMenuItem(Menu1, idImportMusic, _("Import Music"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem8 = new wxMenuItem(Menu1, idExportImage, _("Export Image"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem8);
    MenuItem9 = new wxMenuItem(Menu1, idSave, _("Save"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem9);
    MenuItem11 = new wxMenuItem(Menu1, idLoad, _("Load"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem11);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem4 = new wxMenu();
    MenuItem5 = new wxMenuItem(MenuItem4, idMenuFormation, _("Formation Mode"), wxEmptyString, wxITEM_RADIO);
    MenuItem4->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(MenuItem4, idMenuTransition , _("Transistion Mode"), wxEmptyString, wxITEM_RADIO);
    MenuItem4->Append(MenuItem6);
    Menu3->Append(ID_MENUITEM1, _("Mode"), MenuItem4, wxEmptyString);
    MenuItem7 = new wxMenuItem(Menu3, idNewFormation, _("New Formation"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem7);
    MenuItem10 = new wxMenuItem(Menu3, idSaveFormation, _("Save Formation"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem10);
    MenuBar1->Append(Menu3, _("Edit"));
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
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnPlayButtonClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnPauseButtonClick);
    Connect(ID_SLIDER1,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnSlider1CmdScrollThumbTrack);
    Connect(ID_SLIDER1,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnSlider1CmdScrollThumbRelease);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnEnterTime);
    Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnPanel2Paint,0,this);
    Panel1->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnPanel2LeftDown,0,this);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnNDButtonClick);

    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnChoice1Select);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnAddDancerButtonClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnQuit);
    Connect(idImportMusic,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnImportMusicSelected);
    Connect(idExportImage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnExportImageSelected);
    Connect(idSave,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnFileSaveSelected);
    Connect(idLoad,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnFileLoadSelected);
    Connect(idMenuFormation,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnFormationModeSelected);
    Connect(idMenuTransition ,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnTransitionModeSelected);
    Connect(idNewFormation,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnNewFormationSelected);
    Connect(idSaveFormation,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnSaveFormationSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnAbout);
    //*)
}

FormationMediaPlayerFrame::~FormationMediaPlayerFrame()
{
    //(*Destroy(FormationMediaPlayerFrame)
    //*)
    delete draw;
    delete draw_panel1;
    delete mediactrl1;
}

void FormationMediaPlayerFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void FormationMediaPlayerFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void FormationMediaPlayerFrame::OnImportMusicSelected(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open File"), _(""), _(""), _("music files (*.mp3)|*.mp3"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if(openFileDialog.ShowModal() == wxID_CANCEL) return;

    *TextCtrl1 << openFileDialog.GetPath();

    loaded = mediactrl1->Load(openFileDialog.GetPath());
}

void FormationMediaPlayerFrame::OnPlayButtonClick(wxCommandEvent& event)
{
    if(loaded) mediactrl1->Play();
}

void FormationMediaPlayerFrame::OnPauseButtonClick(wxCommandEvent& event)
{
    if(loaded) mediactrl1->Pause();
}

void FormationMediaPlayerFrame::OnEnterTime(wxCommandEvent& event)
{
    if(TextCtrl2->GetValue().Contains(':')){
        int time = ConvertToTime(TextCtrl2->GetValue());
        if(time <= mediactrl1->Length()){
            mediactrl1->Seek(time);
        }
    }

}

int FormationMediaPlayerFrame::ConvertToTime(wxString time){
    int milli;
    long int minutes, seconds;

    wxString minutes_string = time.BeforeFirst(':');
    wxString seconds_string = time.AfterFirst(':');

    minutes_string.ToLong(&minutes);
    seconds_string.ToLong(&seconds);

    milli = (minutes*60000) + (seconds*1000);

    return milli;
}

void FormationMediaPlayerFrame::OnSlider1CmdScrollThumbTrack(wxScrollEvent& event)
{
    SliderDragged = true;
    mediactrl1->Pause();


}

void FormationMediaPlayerFrame::OnSlider1CmdScrollThumbRelease(wxScrollEvent& event)
{
    SliderDragged = false;
    int position = Slider1->GetValue();
    mediactrl1->Seek(position*1000);
    mediactrl1->Play();
}

void FormationMediaPlayerFrame::OnNDButtonClick(wxCommandEvent& event)
{
    DancerCreatorWindowFrame* CreatorPopup = new DancerCreatorWindowFrame(this);
    CreatorPopup->Show(true);
}

void FormationMediaPlayerFrame::DrawDot(std::shared_ptr<DancerDot>& dd){
    wxCoord h, w;

    wxMemoryDC dc(*dd->d_bmp);
    dc.SetBackground(*wxTRANSPARENT_BRUSH);
    dc.Clear();
    dc.SetBrush(wxBrush(dd->d_color));
    dc.DrawRectangle(wxPoint(0,0), wxSize(50,50));

    dc.GetTextExtent(dd->d_name, &h, &w);
    dc.DrawText(dd->d_name, wxPoint(25 - (h/2),25 - (w/2)));
    dc.SelectObject(wxNullBitmap);

    dd->d_area = new wxRect(*draw, wxPoint(draw->x+50, draw->y+50));
    //dd->d_P1bmp = new wxBitmap(dd->d_bmp->GetSubBitmap(wxRect(0,0, dd->d_bmp->GetWidth(), dd->d_bmp->GetHeight())));
    dd->d_drag = new wxGenericDragImage(*dd->d_bmp);

    BitmapComboBox1->Append(dd->d_name, *dd->d_bmp);
    //wxClientDC pdc(Panel2);
    //pdc.DrawBitmap(*dd->d_bmp, *draw);
    //draw->y = draw->y + 60;
}

void FormationMediaPlayerFrame::OnPanel2Paint(wxPaintEvent& event)
{
    wxPaintDC pdc(Panel1);
    for(auto &x : dancers){
        if(x->DrawnOnP1){
            x->d_drag->DoDrawImage(pdc, x->d_P1point);
        }
    }
    event.Skip();

}

void FormationMediaPlayerFrame::NewDancer(){
    dancers.emplace_back(new DancerDot(*tempName, *tempColor));
    DrawDot(dancers.back());
    //Refresh();
}

void FormationMediaPlayerFrame::OnPanel2LeftDown(wxMouseEvent& event)
{

    int counter, mouseX, mouseY;
    wxPoint pos;
    wxClientDC sdc(Panel1);
    DancerDot* DragPointer = NULL;

    for(auto x : dancers){
        if(x->Contains(event.GetPosition())){
            DragPointer = x.get();
        }
    }

    if(mode == TRANSITION_MODE){
        if(DragPointer != NULL){


            Panel1->Refresh();
            Panel1->Update();
            sdc.SetBrush(*wxTRANSPARENT_BRUSH);
            sdc.SetPen(wxPen(wxColour(246,255,0),3));
            sdc.DrawRectangle(DragPointer->d_drag->GetImageRect(DragPointer->d_P1point));


            }else if(DragPointer == NULL){
            Panel1->Refresh();
            Panel1->Update();

        }
    }

    if(mode == FORMATION_MODE){
        if(DragPointer != NULL){
           DragPointer->d_drag->BeginDrag(wxPoint(0,0), Panel1, false);
           DragPointer->d_drag->Hide();
           while(wxGetMouseState().LeftIsDown()){
                wxGetMousePosition(&mouseX, &mouseY);
                pos.x = mouseX;
                pos.y = mouseY;
                pos = this->ScreenToClient(pos);

                DragPointer->d_drag->Move(pos);
                DragPointer->d_drag->Show();
                counter++;
                if(!(counter%10)) wxYieldIfNeeded();


            }
            DragPointer->d_drag->EndDrag();
            DragPointer->d_P1point = this->ScreenToClient(wxGetMousePosition());
            DragPointer->d_area_p1 = DragPointer->d_drag->GetImageRect(DragPointer->d_P1point);
            /*if(Choice1->GetSelection() != wxNOT_FOUND){
                DragPointer->Transition_Points[Choice1->GetSelection()] = DragPointer->d_P1point;
            }*/

            Panel1->Refresh();


         }
    }


}

void FormationMediaPlayerFrame::OnPanel2LeftDoubleClick(wxMouseEvent& event)
{

   DancerDot* DragPointer = NULL;

    for(auto x : dancers){
        if(x->Contains(event.GetPosition())){
            DragPointer = x.get();
        }
    }

    wxClientDC p1dc(Panel1);
    if(DragPointer != NULL && !(DragPointer->DrawnOnP1)){
        p1dc.DrawBitmap(*DragPointer->d_bmp, *draw_panel1);
        DragPointer->DrawnOnP1 = true;
        DragPointer->d_P1point = *draw_panel1;
        DragPointer->d_area_p1 = wxRect(DragPointer->d_P1point, wxPoint(DragPointer->d_P1point.x + 50, DragPointer->d_P1point.y + 50));
        if(draw_panel1->y + 85 < Panel1->GetMinHeight()){
            draw_panel1->y = draw_panel1->y + 50;
        }else{
            draw_panel1->y = 0;
            draw_panel1->x = draw_panel1->x + 50;
        }
    }

}

void FormationMediaPlayerFrame::OnFormationModeSelected(wxCommandEvent& event)
{
    mode = FORMATION_MODE;
}

void FormationMediaPlayerFrame::OnTransitionModeSelected(wxCommandEvent& event)
{
    mode = TRANSITION_MODE;
}


void FormationMediaPlayerFrame::OnNewFormationSelected(wxCommandEvent& event)
{
    AddTransitionMenuFrame* TransitionMenu = new AddTransitionMenuFrame(this);
    TransitionMenu->Show(true);

}

void FormationMediaPlayerFrame::NewFormation(){
    for(auto &x : dancers){
        x->Transition_Points.push_back(x->d_P1point);
    }

    Choice1->Append(Formation_Name);
    choice ++;
}

void FormationMediaPlayerFrame::OnChoice1Select(wxCommandEvent& event)
{
    wxClientDC cdc(Panel1);
    cdc.Clear();
    for(auto &x : dancers){
        //cdc.DrawBitmap(*x->d_P1bmp, x->Transition_Points[Choice1->GetSelection()]);
        if(x->Transition_Points[Choice1->GetSelection()] != wxDefaultPosition){
                x->d_P1point = x->Transition_Points[Choice1->GetSelection()];
        }
        x->d_drag->DoDrawImage(cdc, x->d_P1point);
        x->d_area_p1 = x->d_drag->GetImageRect(x->d_P1point);
    }
}

void FormationMediaPlayerFrame::OnExportImageSelected(wxCommandEvent& event)
{
    wxBitmap ExportImagebmp(Panel1->GetMinWidth(), Panel1->GetMinHeight());
    wxMemoryDC mdc(ExportImagebmp);
    wxClientDC cdc(Panel1);
    mdc.Blit(wxCoord(0),wxCoord(0), wxCoord(Panel1->GetMinWidth()), wxCoord(Panel1->GetMinHeight()), &cdc, 0, 0);
    mdc.SelectObject(wxNullBitmap);
    wxFileDialog saveFileDialog(this, _("Export Image"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if(saveFileDialog.ShowModal() == wxID_CANCEL) return;

    ExportImagebmp.SaveFile(saveFileDialog.GetPath(),wxBITMAP_TYPE_JPEG );
}


void FormationMediaPlayerFrame::OnFileSaveSelected(wxCommandEvent& event)
{
    std::string points;

    wxFileDialog saveFileDialog(this, _("Save File"), "", "", "JSON files (*.json)|*.json", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if(saveFileDialog.ShowModal() == wxID_CANCEL) return;

    file.open(saveFileDialog.GetPath(),  std::fstream::in | std::fstream::out | std::fstream::trunc);

    for(int b = 0; b < Choice1->GetCount(); b++){
            j.push_back(Choice1->GetString(b).ToStdString());
    }

    file << j << std::endl;

    for(auto &x : dancers){
        dd["name"] = x->d_name.ToStdString();
        dd["color"] = {x->d_color.Red(), x->d_color.Green(), x->d_color.Blue()};
        dd["p1_position"] = {x->d_P1point.x, x->d_P1point.y};
        if(!Choice1->IsEmpty()){
            for(int a = 0; a < Choice1->GetCount(); a++){
                points = std::to_string(x->Transition_Points[a].x) + ',' + std::to_string(x->Transition_Points[a].y);
                dd["Transition_Points"].push_back(points);
            }
        }
        file << dd << std::endl;
        dd["Transition_Points"].clear();
    }

    file.close();

}

void FormationMediaPlayerFrame::OnSaveFormationSelected(wxCommandEvent& event)
{
    if(Choice1->GetSelection() != wxNOT_FOUND){
        for(auto &x : dancers){
            x->Transition_Points[Choice1->GetSelection()] = x->d_P1point;
        }
    }
}

void FormationMediaPlayerFrame::OnFileLoadSelected(wxCommandEvent& event)
{
    std::string line = "";
    std::string jsonString = "";
    int x, y;
    DancerDot* Dot_Pointer = NULL;

     wxFileDialog loadFileDialog(this, _("Open File"), "", "", "JSON files (*.json)|*.json", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if(loadFileDialog.ShowModal() == wxID_CANCEL) return;

    std::ifstream read_file(loadFileDialog.GetPath());

    //read_file.open(loadFileDialog.GetPath(),  std::fstream::in | std::fstream::out | std::fstream::trunc);

    std::getline(read_file, line);

    j = json::parse(line);

    for(json::iterator it = j.begin(); it != j.end(); ++it){
        Choice1->Append(std::string(*it));
        choice++;
    }

    while(std::getline(read_file, line)){
        dd = json::parse(line);

        dancers.emplace_back(new DancerDot(wxString(dd["name"].get<std::string>()), wxColour(dd["color"].at(0), dd["color"].at(1), dd["color"].at(2))));
        DrawDot(dancers.back());
        Dot_Pointer = dancers.back().get();

        if(!(dd["Transition_Points"].empty())){
            Dot_Pointer->DrawnOnP1 = true;
            for(json::iterator it2 = dd["Transition_Points"].begin(); it2 != dd["Transition_Points"].end(); it2++){
                jsonString = it2.value();
                x = std::stoi(jsonString.substr(0, jsonString.find(',')));
                y = std::stoi(jsonString.substr(jsonString.find(',')+1));

                Dot_Pointer->Transition_Points.emplace_back(wxPoint(x,y));
            }
        }


    }

    file.close();

}

void FormationMediaPlayerFrame::OnAddDancerButtonClick(wxCommandEvent& event)
{
    DancerDot* DotPointer = NULL;
    int x = BitmapComboBox1->GetSelection();
    if(x != wxNOT_FOUND){
        DotPointer = dancers.at(x).get();
    }

    wxClientDC p1dc(Panel1);
    if(DotPointer != NULL && !(DotPointer->DrawnOnP1)){
        p1dc.DrawBitmap(*DotPointer->d_bmp, *draw_panel1);
        DotPointer->DrawnOnP1 = true;
        DotPointer->d_P1point = *draw_panel1;
        DotPointer->d_area_p1 = wxRect(DotPointer->d_P1point, wxPoint(DotPointer->d_P1point.x + 50, DotPointer->d_P1point.y + 50));
        if(draw_panel1->y + 85 < Panel1->GetMinHeight()){
            draw_panel1->y = draw_panel1->y + 50;
        }else{
            draw_panel1->y = 0;
            draw_panel1->x = draw_panel1->x + 50;
        }
    }


}
