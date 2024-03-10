#include "MainFrame.h"

MainFrame::MainFrame(const std::string& title,const wxSize& size)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size)
{
    Centre();
}