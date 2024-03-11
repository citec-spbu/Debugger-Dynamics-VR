#include "ParamContainer.h"

wxDEFINE_EVENT(EVT_P_CONTAINER, wxCommandEvent);

BEGIN_EVENT_TABLE(ParamContainer, wxPanel)
   EVT_TEXT_ENTER(wxID_ANY, ParamContainer::OnEnter)
END_EVENT_TABLE()


void ParamContainer::init(wxWindow *parent, int id)
{
    m_parent = parent;

    wxBoxSizer* topsizer = new wxBoxSizer( wxHORIZONTAL );

    param_name_disp = new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition,
         wxSize(Options::WINDOW_WIDTH * Options::PARAM_CONTAINER_DELIM,Options::PARAM_CONTAINER_HEIGHT), // Size
             wxTE_READONLY); // Flags
    param_value_disp = new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition,
         wxSize(Options::WINDOW_WIDTH *(1 - Options::PARAM_CONTAINER_DELIM),Options::PARAM_CONTAINER_HEIGHT), // Size
          wxTE_PROCESS_ENTER, // Flags
            wxTextValidator(wxFILTER_NUMERIC)); // Validator for float numbers

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

// Events
void ParamContainer::OnEnter(wxCommandEvent& evt)
{
    wxCommandEvent event(EVT_P_CONTAINER, AEvents::MainFrameMenuBarIDs::appID_INPUT_FROM_CONTAINERS);
    event.SetString(param_name_disp->GetValue());
    wxPostEvent(m_parent,event);
}