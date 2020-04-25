#include <wx/string.h>
#include <vector>
#include "Transition.h"
#include <wx/gdicmn.h>
#include <wx/dragimag.h>
#include <wx/generic/dragimgg.h>

class DancerDot{
public:
    DancerDot(wxString name, wxColour color){
      d_name = name;
      d_color = color;
      d_bmp = new wxBitmap(50, 50);
      DrawnOnP1 = false;
      d_P1point = wxDefaultPosition;
  }

  bool Contains(wxPoint pnt){
      return (d_area_p1.Contains(pnt) && (d_P1point != wxDefaultPosition));
  }

  ~DancerDot(){
      delete d_bmp;
      delete d_drag;
  }
private:
  wxString d_name;
  wxColour d_color;
  wxBitmap* d_bmp;
  wxRect d_area_p1;
  wxGenericDragImage* d_drag;
  bool DrawnOnP1;
  wxPoint d_P1point;
  std::vector<wxPoint> Transition_Points;


  friend class FormationMediaPlayerFrame;
  friend class DancerCreatorWindowFrame;

};
