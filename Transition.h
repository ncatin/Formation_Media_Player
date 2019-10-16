#include <wx/gdicmn.h>
#include <vector>

class Transition{

  int t_startTime;
  int t_endTime;

  std::vector<wxPoint> path;

  Transition(int startTime, int endTime){
      t_startTime = startTime;
      t_endTime = endTime;
  }

};
