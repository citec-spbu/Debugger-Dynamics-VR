#include <wx/wx.h>
#include <string>

class MainFrame : public wxFrame
{
public:
    MainFrame(const std::string& title, const wxSize& size);

};