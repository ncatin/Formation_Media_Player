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
#include <wx/dcclient.h>
#include <wx/dc.h>
#include <wx/dcmemory.h>
#include <wx/dragimag.h>
#include <wx/generic/dragimgg.h>
#include <wx/utils.h>
#include <wx/dcscreen.h>
//(*InternalHeaders(FormationMediaPlayerFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

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
const long FormationMediaPlayerFrame::ID_PANEL2 = wxNewId();
const long FormationMediaPlayerFrame::idMenuQuit = wxNewId();
const long FormationMediaPlayerFrame::idImportMusic = wxNewId();
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

    tempName = new wxString();

    tempColor = new wxColour();
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
    Slider1 = new wxSlider(this, ID_SLIDER1, 0, 0, 100, wxDefaultPosition, wxSize(129,24), 0, wxDefaultValidator, _T("ID_SLIDER1"));
    GridBagSizer1->Add(Slider1, wxGBPosition(2, 2), wxDefaultSpan, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("Filename"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl1->SetEditable(false);
    GridBagSizer1->Add(TextCtrl1, wxGBPosition(2, 3), wxDefaultSpan, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("Time"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    GridBagSizer1->Add(TextCtrl2, wxGBPosition(2, 4), wxDefaultSpan, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(707,391), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    GridBagSizer1->Add(Panel1, wxGBPosition(0, 0), wxGBSpan(2, 5), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button3 = new wxButton(this, ID_BUTTON3, _("New Dancer"), wxDefaultPosition, wxSize(111,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    GridBagSizer1->Add(Button3, wxGBPosition(0, 5), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxSize(143,333), wxTAB_TRAVERSAL|wxVSCROLL, _T("ID_PANEL2"));
    GridBagSizer1->Add(Panel2, wxGBPosition(1, 5), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(GridBagSizer1, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuItem3 = new wxMenuItem(Menu1, idImportMusic, _("Import Music"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
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
    Panel2->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnPanel2LeftDoubleClick,0,this);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnQuit);
    Connect(idImportMusic,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnImportMusicSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FormationMediaPlayerFrame::OnAbout);
    //*)
}

FormationMediaPlayerFrame::~FormationMediaPlayerFrame()
{
    //(*Destroy(FormationMediaPlayerFrame)
    //*)
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
    dc.DrawCircle(wxPoint(25,25), 25);

    dc.GetTextExtent(dd->d_name, &h, &w);
    dc.DrawText(dd->d_name, wxPoint(25 - (h/2),25 - (w/2)));
    dc.SelectObject(wxNullBitmap);

    dd->d_area = new wxRect(*draw, wxPoint(draw->x+50, draw->y+50));
    dd->d_P1bmp = new wxBitmap(dd->d_bmp->GetSubBitmap(wxRect(0,0, dd->d_bmp->GetWidth(), dd->d_bmp->GetHeight())));
    dd->d_drag = new wxGenericDragImage(*dd->d_P1bmp);
    wxClientDC pdc(Panel2);
    pdc.DrawBitmap(*dd->d_bmp, *draw);
    draw->y = draw->y + 60;
}

void FormationMediaPlayerFrame::OnPanel2Paint(wxPaintEvent& event)
{
    wxPaintDC pdc(Panel1);
    for(auto &x : dancers){
        if(x->DrawnOnP1) x->d_drag->DoDrawImage(pdc, *x->d_P1point);
        //pdc.DrawBitmap(*x->d_P1bmp, *x->d_P1point);
        //draw->y = draw->y + 70;
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
    if(DragPointer != NULL){
       DragPointer->d_drag->BeginDrag(wxPoint(0,0)/*DragPointer->d_area_p1.GetTopLeft()*/, Panel1, false);
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
        *DragPointer->d_P1point = this->ScreenToClient(wxGetMousePosition());
        DragPointer->d_area_p1 = DragPointer->d_drag->GetImageRect(*DragPointer->d_P1point);//wxRect(*DragPointer->d_P1point, wxPoint(DragPointer->d_P1point->x + 50, DragPointer->d_P1point->y + 50));
        Panel1->Refresh();


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
        p1dc.DrawBitmap(*DragPointer->d_P1bmp, *draw_panel1);
        DragPointer->DrawnOnP1 = true;
        DragPointer->d_P1point = new wxPoint(*draw_panel1);
        DragPointer->d_area_p1 = wxRect(*DragPointer->d_P1point, wxPoint(DragPointer->d_P1point->x + 50, DragPointer->d_P1point->y + 50));
        if(draw_panel1->y + 85 < Panel1->GetMinHeight()){
            draw_panel1->y = draw_panel1->y + 50;
        }else{
            draw_panel1->y = 0;
            draw_panel1->x = draw_panel1->x + 50;
        }
    }

}
