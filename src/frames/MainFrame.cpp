#include "MainFrame.h"
#include <wx/numdlg.h>
#include "../elements/ParamContainer.h"
#include "../Constants.h"

// ----------  Events  ----------
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
   EVT_MENU(AEvents::MainFrameMenuBarIDs::appINPUT_PATH_TO_IO, MainFrame::startFindPathInput)
   EVT_MENU(AEvents::MainFrameMenuBarIDs::appOUTPUT_PATH_TO_IO, MainFrame::startFindPathOutput)
   EVT_MENU(AEvents::MainFrameMenuBarIDs::appREQUEST_ALL_PARAMS, MainFrame::requestAllParams)
   EVT_MENU(AEvents::MainFrameMenuBarIDs::appCHANGE_IO_RATE, MainFrame::changeIORate)
   EVT_MENU(AEvents::MainFrameMenuBarIDs::appENABLE_IO_PROCESS, MainFrame::changeState)
   EVT_MENU(AEvents::MainFrameMenuBarIDs::appDISABLE_IO_PROCESS, MainFrame::changeState)
   EVT_COMMAND(AEvents::MainFrameMenuBarIDs::appID_INPUT_FROM_CONTAINERS, EVT_P_CONTAINER, MainFrame::inputEventFromPContainers)
END_EVENT_TABLE()

MainFrame::MainFrame(const std::string& title,const wxSize& size)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size),
       processIORate(1000.0 / Options::EXCHANGE_PER_SECOND),
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
    // -- State menu --   
    wxMenu* m_pStateMenu = new wxMenu();
    // Set menu popup buttons
    m_pStateMenu->Append(AEvents::MainFrameMenuBarIDs::appENABLE_IO_PROCESS, _T("&Enable read/write"));
    m_pStateMenu->Append(AEvents::MainFrameMenuBarIDs::appDISABLE_IO_PROCESS, _T("&Disable read/write"));
    m_pMenuBar->Append(m_pStateMenu, _T("&StateIO"));
    
    // ------- Options menu -------
    wxMenu* m_pOptionsMenu = new wxMenu();
    // Set menu popup buttons
    m_pOptionsMenu->Append(AEvents::MainFrameMenuBarIDs::appINPUT_PATH_TO_IO, _T("&Set path to Input-file"));
    m_pOptionsMenu->Append(AEvents::MainFrameMenuBarIDs::appOUTPUT_PATH_TO_IO, _T("&Set path to Output-file"));
    m_pOptionsMenu->Append(AEvents::MainFrameMenuBarIDs::appREQUEST_ALL_PARAMS, _T("&Request all params"));
    m_pOptionsMenu->Append(AEvents::MainFrameMenuBarIDs::appCHANGE_IO_RATE, _T("&Change read/write rate"));
    m_pMenuBar->Append(m_pOptionsMenu, _T("&Options"));
    // Panel with ParamContainers  
    panel = new wxScrolled<wxPanel>(this, wxID_ANY, wxDefaultPosition, wxSize(Options::WINDOW_WIDTH, Options::WINDOW_HEIGHT));
    panel->SetScrollRate(0, FromDIP(10));
    // Sizers
    mainsizer = new wxBoxSizer( wxVERTICAL );  
    panelsizer = new wxBoxSizer( wxVERTICAL );  

    panel->SetSizer(panelsizer); // While the program is running, we will add containers to the sizer dynamically
    // Text Ctrl about amount of params
    wxTextCtrl* static_text_amount_of_params = new wxTextCtrl( this, wxID_ANY, "Amount of params:", wxDefaultPosition,
         wxDefaultSize, // Size
             wxTE_READONLY);
    amount_of_params = new wxTextCtrl( this, wxID_ANY, "0", wxDefaultPosition,
         wxDefaultSize, // Size
             wxTE_READONLY);
    wxBoxSizer* sizer_a_o_p = new wxBoxSizer( wxHORIZONTAL );
    sizer_a_o_p->Add(static_text_amount_of_params, wxALIGN_LEFT);
    sizer_a_o_p->Add(amount_of_params, wxALIGN_RIGHT);
    //
    mainsizer->Add(panel, 1, wxEXPAND | wxALL | wxALIGN_TOP, 1);
    mainsizer->Add(sizer_a_o_p, 0, wxALIGN_CENTER_HORIZONTAL, 0);
    SetSizer(mainsizer);
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

    // -------- Start IOProtocol --------
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
// ---------- Containers functions ----------
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
    auto res_obj = panelsizer->Add(container,
        0,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        1 );
    if(res_obj != nullptr)
    {
        amount_of_containers++;
        updateAmountOfContainersTextCtrl(amount_of_containers);
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
        amount_of_containers--;
        updateAmountOfContainersTextCtrl(amount_of_containers);
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
// ---------- Main Loop function ----------
void MainFrame::processIO(float deltaTime)
{
    if(protocol.getStatus() && stateIO)
    {
        buffer_time += deltaTime;
        
        if(buffer_time > processIORate)
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
// ---------- Events functions ----------
void MainFrame::inputEventFromPContainers(wxCommandEvent &event) // Event after 'enter' on params 
{    
    wxLogGeneric(wxLOG_Message, wxString::Format("Send param to outfile:%s", event.GetString().ToStdString()));
    auto param_info = event.GetString().ToStdString();
    protocol.changeParam(param_info.substr(0, param_info.find("=")), std::stod(param_info.substr(param_info.find("=") + 1, param_info.size()))); // Rewrite in the future
}

void MainFrame::startFindPathInput(wxCommandEvent &event)
{   
    wxFileDialog* openFileDialog = new wxFileDialog(nullptr,  _("Open input file"), "", "",
        "", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

	if (openFileDialog->ShowModal() == wxID_OK) 
	{
        std::string path = openFileDialog->GetPath().ToStdString();
        protocol.setInFile(path);
    }
    else
    {
        wxMessageDialog *dial = new wxMessageDialog(nullptr, 
        wxT("File isn't loaded"), wxT("Info about operation"), wxOK);
        dial->ShowModal();
    }

	// --- Clean up after ourselves ---
	openFileDialog->Destroy();
}
void MainFrame::startFindPathOutput(wxCommandEvent &event)
{
    wxFileDialog* openFileDialog = new wxFileDialog(nullptr,  _("Open output file"), "", "",
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

void MainFrame::changeIORate(wxCommandEvent &event)
{
    wxNumberEntryDialog* openNumberDialog = new wxNumberEntryDialog(nullptr,  _("Write the number of updates per second"), "", "Updates per second",
        static_cast<long>(1000.0 / processIORate), 1, 100);
    if (openNumberDialog->ShowModal() == wxID_OK) 
	{
        double perUpdate = static_cast<double>(openNumberDialog->GetValue()); 

        processIORate = 1000.0 / perUpdate;
        wxLogGeneric(wxLOG_Message, wxString::Format("Update IORate:%i", openNumberDialog->GetValue()));
    }
    else
    {
        wxLogGeneric(wxLOG_Error, wxString("Can't open modal window for input rate"));
    }
    openNumberDialog->Destroy();
}

void MainFrame::changeState(wxCommandEvent &event)
{
    if(event.GetId() == AEvents::MainFrameMenuBarIDs::appENABLE_IO_PROCESS)
    {
        stateIO = true;
        wxLogGeneric(wxLOG_Message, wxString("Enable IO processing"));
    }
    else
    {
        stateIO = false;
        wxLogGeneric(wxLOG_Message, wxString("Disable IO processing"));
    }
}

void MainFrame::updateAmountOfContainersTextCtrl(int amount)
{
    amount_of_params->SetValue(wxString::Format("%i",amount));
}