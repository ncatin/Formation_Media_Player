/***************************************************************
 * Name:      FormationMediaPlayerApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2019-10-11
 * Copyright:  ()
 * License:
 **************************************************************/

#include "FormationMediaPlayerApp.h"

//(*AppHeaders
#include "FormationMediaPlayerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(FormationMediaPlayerApp);

bool FormationMediaPlayerApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	FormationMediaPlayerFrame* Frame = new FormationMediaPlayerFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
