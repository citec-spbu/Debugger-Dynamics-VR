#include "ParamContainer.h"

// Events
wxDEFINE_EVENT(EVT_P_CONTAINER, wxCommandEvent);

BEGIN_EVENT_TABLE(ParamContainer, wxPanel)
   EVT_SPINCTRLDOUBLE(wxID_ANY, ParamContainer::OnSpin)   
   EVT_TEXT_ENTER(wxID_ANY, ParamContainer::OnEnter)   
END_EVENT_TABLE()


void ParamContainer::init(wxWindow *parent, int id)
{
    m_parent = parent;

    wxBoxSizer* topsizer = new wxBoxSizer( wxHORIZONTAL );
    // Add visible and controll texts
    param_name_disp = new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition,
         wxSize(Options::WINDOW_WIDTH * Options::PARAM_CONTAINER_DELIM,Options::PARAM_CONTAINER_HEIGHT), // Size
             wxTE_READONLY); // Flags
    param_value_disp = new wxSpinCtrlDouble( this, wxID_ANY, "", wxDefaultPosition,
         wxSize(Options::WINDOW_WIDTH *(1 - Options::PARAM_CONTAINER_DELIM),Options::PARAM_CONTAINER_HEIGHT), // Size
        wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER
    );
    // Param_value_text_crtl settings
    param_value_disp->SetIncrement(Options::PARAM_INCREMENT_VALUE);
    param_value_disp->SetRange(0, Options::PARAM_MAX_VALUE);
    topsizer->Add(
        param_name_disp, 0, wxEXPAND, FromDIP(Options::PARAM_BORDER_SIZE));  
    topsizer->Add(
        param_value_disp, 1, wxEXPAND, FromDIP(Options::PARAM_BORDER_SIZE)); 
    
    SetSizer(topsizer);
}

ParamContainer::ParamContainer(wxWindow *parent, int id)
        : wxPanel(parent, id, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER)
{
    init(parent, id);
}

ParamContainer::ParamContainer(wxWindow *parent, int id, const std::string& param_name, double value)
        : wxPanel(parent, id, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER)
{
    init(parent, id);
    param_name_disp->SetValue(param_name);
    param_value_disp->SetValue(wxString::Format(wxT("%f"), value));    
}

void ParamContainer::setValue(double value)
{
    param_value_disp->SetValue(wxString::Format(wxT("%f"), value));
}

void ParamContainer::OnEnter(wxCommandEvent& evt)
{
    // Helps to apply a new value (Bad dicision - maybe in the future will be correct)
    // If we don't trigger Focus event, we do not take a new value in text ctrl  
    param_name_disp->SetFocus(); 
    param_value_disp->SetFocus();
    //
    // Send Event to MainFrame for sending with specific param and value
    wxCommandEvent event(EVT_P_CONTAINER, AEvents::MainFrameMenuBarIDs::appID_INPUT_FROM_CONTAINERS);
    event.SetString(wxString::Format("%s=%f", param_name_disp->GetValue(), param_value_disp->GetValue()));
    wxPostEvent(m_parent,event);
}

void ParamContainer::OnSpin(wxSpinDoubleEvent& evt)
{
    // Send Event to MainFrame for sending with specific param and value
    wxCommandEvent event(EVT_P_CONTAINER, AEvents::MainFrameMenuBarIDs::appID_INPUT_FROM_CONTAINERS);
    event.SetString(wxString::Format("%s=%f", param_name_disp->GetValue(), param_value_disp->GetValue()));
    wxPostEvent(m_parent,event);
}