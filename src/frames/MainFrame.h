#include <wx/wx.h>
#include <map>

#include "../elements/ParamContainer.h"

class MainFrame : public wxFrame
{
private: 
    wxBoxSizer* topsizer;
    wxScrolled<wxPanel>* panel;
    void startSetNamesIO(wxCommandEvent &event);
    void startFindPathIO(wxCommandEvent &event);
    void inputEventFromPContainers(wxCommandEvent &event);

    std::map<std::string, ParamContainer*> containers; 
   
public:
    MainFrame(const std::string& title,const wxSize& size);


// Containers functions
    bool addContainer(const std::string& param, double value = 0.0);
    bool deleteContainer(const std::string& param);
    bool updateContainer(const std::string& param_name, double n_value);

protected:
	DECLARE_EVENT_TABLE()

};
