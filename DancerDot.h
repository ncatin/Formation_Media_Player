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
      transition_select = false;
  }

  bool Contains(wxPoint pnt){
      return (d_area->Contains(pnt) || d_area_p1.Contains(pnt));
  }

  ~DancerDot(){
      delete d_P1bmp;
      delete d_bmp;
      delete d_area;
      delete d_drag;
      delete d_P1point;
  }
private:
  wxString d_name;
  wxColour d_color;
  wxBitmap* d_bmp;
  wxBitmap* d_P1bmp;
  wxRect* d_area;
  wxRect d_area_p1;
  wxGenericDragImage* d_drag;
  bool DrawnOnP1, transition_select;
  wxPoint* d_P1point;

  std::vector<Transition> transition;



  friend class FormationMediaPlayerFrame;
  friend class DancerCreatorWindowFrame;

};
