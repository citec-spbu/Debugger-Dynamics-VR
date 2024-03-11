#include "MainFrame.h"

// Events
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
   EVT_MENU(AEvents::MainFrameMenuBarIDs::appID_PATH_TO_IO, MainFrame::startFindPathIO)
   EVT_MENU(AEvents::MainFrameMenuBarIDs::appID_NAMES_IO, MainFrame::startSetNamesIO)
   EVT_COMMAND(AEvents::MainFrameMenuBarIDs::appID_INPUT_FROM_CONTAINERS, EVT_P_CONTAINER, MainFrame::inputEventFromPContainers)
END_EVENT_TABLE()


MainFrame::MainFrame(const std::string& title,const wxSize& size)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size)
{
    // Create some components
    // Menu bar
    wxMenuBar *m_pMenuBar = new wxMenuBar(); 
    SetMenuBar(m_pMenuBar);
    wxMenu* m_pFileMenu = new wxMenu();
    m_pFileMenu->Append(AEvents::MainFrameMenuBarIDs::appID_PATH_TO_IO, _T("&Set path to IO-files"));
    m_pFileMenu->Append(AEvents::MainFrameMenuBarIDs::appID_NAMES_IO, _T("&Set names of IO-files"));

    m_pMenuBar->Append(m_pFileMenu, _T("&File"));
    // Panel with ParamContainers  
    panel = new wxScrolled<wxPanel>(this, wxID_ANY);
    panel->SetScrollRate(0, FromDIP(10));

    topsizer = new wxBoxSizer( wxVERTICAL );    

    panel->SetSizerAndFit(topsizer);

    addContainer("SomeParams");
    addContainer("SomeParams1");
    addContainer("SomeParams2");
    addContainer("SomeParams3");
    addContainer("SomeParams4");
    deleteContainer("SomeParams");
    deleteContainer("SomeParams3");
    addContainer("SomeParams11");
    addContainer("SomeParams12");
}
// Containers functions
bool MainFrame::addContainer(const std::string& param, double value)
{
    if(containers.find(param) != containers.end())
    {
        return false;
    }
    ParamContainer* container = new ParamContainer(panel, wxID_ANY, param, value);   
    // Add to sizer/panel (to the end)
    auto res_obj = topsizer->Add(container,
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
    if(res_obj != nullptr)
    {
        containers[param] = container;    
        return true;
    }
    return false;
}

bool MainFrame::deleteContainer(const std::string& param)
{
    if(containers.find(param) != containers.end())
    {
        containers[param]->Destroy(); // Destroy ParamContainer
        containers.erase(param); 
        return true;
    }
    return false;
}
bool MainFrame::updateContainer(const std::string& param, double n_value)
{
    if(containers.find(param) != containers.end())
    {
        containers[param]->setValue(n_value);
        return true;
    }
    return false;
}

//Events functions
void MainFrame::inputEventFromPContainers(wxCommandEvent &event)
{    
    addContainer("SomeParams10");
    panel->Layout(); // For correctly show new Container
}

// Realise in the future   
void MainFrame::startSetNamesIO(wxCommandEvent &event)
{    
}
void MainFrame::startFindPathIO(wxCommandEvent &event)
{
}
