#include "MainFrame.h"
#include "../elements/ParamContainer.h"
#include "../Constants.h"

// Events
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
   EVT_MENU(AEvents::MainFrameMenuBarIDs::appINPUT_PATH_TO_IO, MainFrame::startFindPathInput)
   EVT_MENU(AEvents::MainFrameMenuBarIDs::appOUTPUT_PATH_TO_IO, MainFrame::startFindPathOutput)
   EVT_MENU(AEvents::MainFrameMenuBarIDs::appREQUEST_ALL_PARAMS, MainFrame::requestAllParams)
   EVT_COMMAND(AEvents::MainFrameMenuBarIDs::appID_INPUT_FROM_CONTAINERS, EVT_P_CONTAINER, MainFrame::inputEventFromPContainers)
END_EVENT_TABLE()

MainFrame::MainFrame(const std::string& title,const wxSize& size)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size),
       config(Options::CONFIG_PATH) // Load config file
{
    wxLogGeneric(wxLOG_Message, wxT("Start application - create main frame..."));
    if(!config.isCorrectRead())
    {
        wxLogGeneric(wxLOG_Error, wxT("Cannot find or open config file..."));
    }
    // Create some components
    // Menu bar
    wxMenuBar *m_pMenuBar = new wxMenuBar(); 
    SetMenuBar(m_pMenuBar);
    wxMenu* m_pFileMenu = new wxMenu();
    // Set menu popup buttons
    m_pFileMenu->Append(AEvents::MainFrameMenuBarIDs::appINPUT_PATH_TO_IO, _T("&Set path to Input-file"));
    m_pFileMenu->Append(AEvents::MainFrameMenuBarIDs::appOUTPUT_PATH_TO_IO, _T("&Set path to Output-file"));
    m_pFileMenu->Append(AEvents::MainFrameMenuBarIDs::appREQUEST_ALL_PARAMS, _T("&Request all params"));
    m_pMenuBar->Append(m_pFileMenu, _T("&Options"));
    // Panel with ParamContainers  
    panel = new wxScrolled<wxPanel>(this, wxID_ANY);
    panel->SetScrollRate(0, FromDIP(10));
    // Main Sizer
    topsizer = new wxBoxSizer( wxVERTICAL );  
    panel->SetSizerAndFit(topsizer); // While the program is running, we will add containers to the sizer dynamically
    
    wxLogGeneric(wxLOG_Message, "Created main frame.");    
    wxLogGeneric(wxLOG_Message, "Start FileIOProtocol");
    // Read from config data
    std::optional<std::string> inp = std::nullopt;
    std::optional<std::string> out = std::nullopt;

    if(config.isCorrectRead())
    {
        inp = config.getParam("InputFILE");
        out = config.getParam("OutputFILE"); 
    }    
    // Start IOProtocol
    if(inp && out)
    {  
        protocol.setInFile(*inp);
        protocol.setOutFile(*out);
    }
    else // If we can't take configs  
    {
        protocol.setInFile(Options::DEFAULT_IN_FILE_PATH);
        protocol.setOutFile(Options::DEFAULT_OUT_FILE_PATH);
    }    

    if(protocol.getStatus())
    {
        protocol.sendRequestForAllParams();
        wxLogGeneric(wxLOG_Message, wxString::Format("Correct started FileIOProtocol input:%s output:%s",*inp,*out));
    }
    else
    {
        wxLogGeneric(wxLOG_Error, "FileIOProtocol isn't started");
    }
    
}
// Containers functions
bool MainFrame::addContainer(const std::string& param, double value, bool update)
{
    wxLogGeneric(wxLOG_Message, wxString::Format("Add new container:%s %f", param, value));
    if(containers.find(param) != containers.end())
    {
        wxLogGeneric(wxLOG_Message, "Container already created.");
        if(update) // If container exists, and flag update = true -> we update container
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
    wxLogGeneric(wxLOG_Message, wxString("Delete container:" + param));
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
    wxLogGeneric(wxLOG_Message, wxString::Format("Update container:%s %f", param, n_value));
    if(containers.find(param) != containers.end())
    {
        containers[param]->setValue(n_value);
        return true;
    }
    return false;
}
//Events functions
void MainFrame::inputEventFromPContainers(wxCommandEvent &event) // Event after 'enter' on params 
{    
    wxLogGeneric(wxLOG_Message, wxString::Format("Send param to outfile:%s", event.GetString().ToStdString()));
    auto param_info = event.GetString().ToStdString();
    protocol.changeParam(param_info.substr(0, param_info.find("=")), std::stod(param_info.substr(param_info.find("=") + 1, param_info.size()))); // Rewrite in the future
}
// Main Loop function
void MainFrame::processIO()
{
    // Calculate delta
    static clock_t last_time = 0; 
    clock_t time = std::clock();
    double delta = time - last_time;
    last_time = time;

    if(protocol.getStatus())
    {
        buffer_time += delta;
        
        if(buffer_time > 1000.0 / Options::EXCHANGE_PER_SECOND)
        {
            buffer_time = 0.0;   

            auto data = protocol.exchange();
            for(auto& item : data)
            {
                addContainer(item.first, item.second, true);
            }
            panel->FitInside(); // For correct showing and update Layout and ... 
        }
    }
}

void MainFrame::startFindPathInput(wxCommandEvent &event)
{   
    wxFileDialog* openFileDialog = new wxFileDialog(NULL,  _("Open input file"), "", "",
        "", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

	if (openFileDialog->ShowModal() == wxID_OK) 
	{
        std::string path = openFileDialog->GetPath().ToStdString();
        protocol.setInFile(path);
    }
    else
    {
        wxMessageDialog *dial = new wxMessageDialog(NULL, 
        wxT("File isn't loaded"), wxT("Info about operation"), wxOK);
        dial->ShowModal();
    }

	// --- Clean up after ourselves ---
	openFileDialog->Destroy();
}
void MainFrame::startFindPathOutput(wxCommandEvent &event)
{
    wxFileDialog* openFileDialog = new wxFileDialog(NULL,  _("Open output file"), "", "",
        "", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

	if (openFileDialog->ShowModal() == wxID_OK) 
	{
        std::string path = openFileDialog->GetPath().ToStdString();
        protocol.setOutFile(path);
    }
    else
    {
        wxMessageDialog *dial = new wxMessageDialog(NULL, 
        wxT("File isn't loaded"), wxT("Info about operation"), wxOK);
        dial->ShowModal();
    }

	// --- Clean up after ourselves ---
	openFileDialog->Destroy();
}

void MainFrame::requestAllParams(wxCommandEvent &event)
{
    protocol.sendRequestForAllParams();
}
