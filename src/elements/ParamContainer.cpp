#include "ParamContainer.h"

void ParamContainer::init(wxWindow *parent, int id)
{
    m_parent = parent;

    Connect(wxEVT_PAINT, wxPaintEventHandler(ParamContainer::OnPaint));

    wxBoxSizer* topsizer = new wxBoxSizer( wxHORIZONTAL );

    param_name_disp = new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition,
         wxSize(Options::WINDOW_WIDTH * Options::PARAM_CONTAINER_DELIM,Options::PARAM_CONTAINER_HEIGHT), // Size
             wxTE_READONLY); // Flags
    param_value_disp = new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition,
         wxSize(Options::WINDOW_WIDTH *(1 - Options::PARAM_CONTAINER_DELIM),Options::PARAM_CONTAINER_HEIGHT)); // Size

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

ParamContainer::ParamContainer(wxWindow *parent, int id, const std::string& param_name)
        : wxPanel(parent, id, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER)
{
    init(parent, id);
    param_name_disp->SetValue(param_name);
}

void ParamContainer::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

}

