
#include "wx/timer.h"

class wxMediaPlayerTimer : public wxTimer{

    FormationMediaPlayerFrame* m_frame;
    wxMediaPlayerTimer(FormationMediaPlayerFrame* frame) {m_frame = frame;}

    void Notify(){
        wxMediaCtrl* currentMediaCtrl = m_frame->mediactrl1;

        wxLongLong Length = currentMediaCtrl->Length();
        int nMinutes = (int) (Length / 60000).GetValue();
        int nSeconds = (int) ((Length % 60000)/1000).GetValue();

        wxString sDuration;
        sDuration.Printf("%2i:%02i", nMinutes, nSeconds);

        wxLongLong Tell = currentMediaCtrl->Tell();
        nMinutes = (int) (Tell / 60000).GetValue();
        nSeconds = (int) ((Tell % 60000)/1000).GetValue();

        wxString sPosition;
        sPosition.Printf("%2i:%02i", nMinutes, nSeconds);

        if(!(m_frame->TextCtrl2->HasFocus())) m_frame->TextCtrl2->ChangeValue(sPosition);

        m_frame->Slider1->SetRange(0, (int)(Length / 1000).GetValue());

        if(!(m_frame->SliderDragged))m_frame->Slider1->SetValue((long)(Tell / 1000).GetValue());

    }

    friend class FormationMediaPlayerFrame;

};
