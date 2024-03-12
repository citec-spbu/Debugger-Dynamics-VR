#include <wx/wx.h>
#include <map>
#include <ctime>
#include <queue>

#include "../elements/ParamContainer.h"
#include "../utility/protocol.h"
#include "../utility/config.h"
class MainFrame : public wxFrame
{
private: 
    // Components
    wxBoxSizer* topsizer;
    wxScrolled<wxPanel>* panel;
    // Events functions
    void startSetNamesIO(wxCommandEvent &event);
    void startFindPathIO(wxCommandEvent &event);
    void inputEventFromPContainers(wxCommandEvent &event);
    // Containers 
    std::map<std::string, ParamContainer*> containers; 
    // Protocol IO
    Utility::IOFileProtocol protocol;    
    std::queue<std::vector<std::string>> send_buffer; 
    // Config
    Utility::Config config;
    double buffer_time;
public:
    MainFrame(const std::string& title,const wxSize& size);

    
    // Containers functions
    bool addContainer(const std::string& param, double value = 0.0, bool update = false);
    bool deleteContainer(const std::string& param);
    bool updateContainer(const std::string& param_name, double n_value);

    // Loop function
    void processRead();
protected:
	DECLARE_EVENT_TABLE()

};
