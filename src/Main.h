#include <wx/wx.h>
#include "frames/MainFrame.h"
#include "Constants.h"



class MyApp : public wxApp
{
private:  
  MainFrame *frame;
  void onIdle(wxIdleEvent& evt);
public:
  virtual bool OnInit();

protected:
  DECLARE_EVENT_TABLE()  
};