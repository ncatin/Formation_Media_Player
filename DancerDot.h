#include <wx/string.h>
#include <vector>
#include "Transition.h"
#include <wx/gdicmn.h>
#include <wx/dragimag.h>

class DancerDot{
public:
    DancerDot(wxString name, wxColour color){
      d_name = name;
      d_color = color;
      d_bmp = new wxBitmap(70, 70);
      d_area = new wxRegion(*d_bmp);
      d_drag = new wxDragImage(*d_bmp);
  }

  bool Contains(wxPoint pnt){
      return d_area->Contains(pnt);
  }

  ~DancerDot(){
      delete d_bmp;
      delete d_area;
      delete d_drag;
  }
private:
  wxString d_name;
  wxColour d_color;
  wxBitmap* d_bmp;
  wxRegion* d_area;
  wxDragImage* d_drag;

  std::vector<Transition> transition;



  friend class FormationMediaPlayerFrame;
  friend class DancerCreatorWindowFrame;

};
