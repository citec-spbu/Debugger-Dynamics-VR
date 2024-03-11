#ifndef ParamContainer_H
#define ParamContainer_H
#include <string>
#include "../Constants.h"
#include "wx/wx.h"

class ParamContainer : public wxPanel
{
private:
    
    wxTextCtrl* param_name_disp;
    wxTextCtrl* param_value_disp; 
    wxWindow* m_parent;
    void init(wxWindow *parent, int id);
public:
    ParamContainer(wxWindow *parent, int id, const std::string& param_name);
    ParamContainer(wxWindow *parent, int id);



    void OnSize(wxSizeEvent& event);
    void OnPaint(wxPaintEvent& event);  

};

#endif