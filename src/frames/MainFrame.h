#ifndef MainFrame_H
#define MainFrame_H

#include <wx/wx.h>
#include <map>
#include <queue>
#include <FileProtocol.h>
#include "../utility/config.h"

class ParamContainer;

class MainFrame : public wxFrame
{
private: 
    // Components
    wxBoxSizer* topsizer;
    wxScrolled<wxPanel>* panel;
    // Events functions
    void startFindPathInput(wxCommandEvent &event);
    void startFindPathOutput(wxCommandEvent &event);
    void requestAllParams(wxCommandEvent &event);
    void inputEventFromPContainers(wxCommandEvent &event);
    void changeIORate(wxCommandEvent &event);
    void changeState(wxCommandEvent &event);
    // Containers 
    std::map<std::string, ParamContainer*> containers; 
    // Protocol IO
    FileProtocol protocol;
    float processIORate; // Default value in milliseconds
    bool stateIO = true;
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
    void processIO(float deltaTime);
protected:
	DECLARE_EVENT_TABLE()
};

#endif