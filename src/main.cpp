#include "Main.h"
// Implement "main" function for wxWidgets
IMPLEMENT_APP(MyApp)

BEGIN_EVENT_TABLE(MyApp, wxApp)
EVT_IDLE(MyApp::onIdle)
END_EVENT_TABLE()

bool MyApp::OnInit() 
{
    wxInitAllImageHandlers();
    
    frame = new MainFrame(Options::APP_NAME,
                                         wxSize(Options::WINDOW_WIDTH, Options::WINDOW_HEIGHT));

    frame->SetIcons(wxIconBundle(Options::APP_LOGO_PATH));
    frame->Show(true);
    

    return true;
}

void MyApp::onIdle(wxIdleEvent& evt)
{
    frame->processRead();
}   