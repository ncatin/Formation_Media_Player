#include <wx/string.h>
#include <vector>
#include "Transition.h"
#include <wx/gdicmn.h>

class DancerDot{
public:
    DancerDot(wxString name, wxColour color){
      d_name = name;
      d_color = color;
      d_bmp = new wxBitmap;
  }

  ~DancerDot(){
      delete d_bmp;
  }
private:
  wxString d_name;
  wxColour d_color;
  wxBitmap* d_bmp;

  std::vector<Transition> transition;



  friend class FormationMediaPlayerFrame;
  friend class DancerCreatorWindowFrame;

};
