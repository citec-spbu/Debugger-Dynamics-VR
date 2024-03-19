#ifndef ParamContainer_H
#define ParamContainer_H

#include <string>
#include "../Constants.h"
#include "wx/wx.h"
#include <wx/spinctrl.h>

// Make event for process enter in containers 
wxDECLARE_EVENT(EVT_P_CONTAINER, wxCommandEvent);

class ParamContainer : public wxPanel
{
private:        
    wxTextCtrl* param_name_disp;
    wxSpinCtrlDouble* param_value_disp;
     
    wxWindow* m_parent;
    void init(wxWindow *parent, int id);
    void OnEnter(wxCommandEvent& evt);
    void OnSpin(wxSpinDoubleEvent& evt);
public:
    ParamContainer(wxWindow *parent, int id, const std::string& param_name, double value = 0.0);
    ParamContainer(wxWindow *parent, int id);

    void setValue(double value);
protected: 
    DECLARE_EVENT_TABLE();
};

#endif