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
    // !!! Must Correct in the future 
    protocol = Utility::IOFileProtocol("C:\\Projects\\university projects\\TestPrj_cut_Pack\\Windows\\TestPrj\\Content\\dbutil\\params_out.txt",
     "C:\\Projects\\university projects\\TestPrj_cut_Pack\\Windows\\TestPrj\\Content\\dbutil\\params_in.txt");
    send_buffer.push({" "});
}
// Containers functions
bool MainFrame::addContainer(const std::string& param, double value, bool update)
{
    if(containers.find(param) != containers.end())
    {
        if(update)
        {
            return updateContainer(param, value);
        }
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
    send_buffer.push({event.GetString().ToStdString()});
}

void MainFrame::processRead()
{
    // Calculate delta
    static clock_t last_time = 0; 
    clock_t time = std::clock();
    double delta = time - last_time;
    last_time = time;
    //
    buffer_time += delta;
    
    if(buffer_time > 1000.0 / Options::EXCHANGE_PER_SECOND)
    {
        buffer_time = 0.0;    
        std::vector<std::string> send_data = {};
        if(!send_buffer.empty())
        {
            send_data = std::move(send_buffer.front()); 
            send_buffer.pop();           
        }
        auto data = protocol.exchange(send_data);
        if(data)
        {
            for(auto& item : *data)
            {
                if(!item.empty())
                {
                    size_t split_index = item.find('=');
                    addContainer(item.substr(0,split_index), std::stod(item.substr(split_index + 1, item.size())), true);
                    
                }
            }
            panel->FitInside();

        }

    }
}

// Realise in the future   
void MainFrame::startSetNamesIO(wxCommandEvent &event)
{    
}
void MainFrame::startFindPathIO(wxCommandEvent &event)
{
}
