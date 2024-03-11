#include "main.h"
// Implement "main" function for wxWidgets
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    
    MainFrame *frame = new MainFrame(Options::APP_NAME,
                                         wxSize(Options::WINDOW_WIDTH, Options::WINDOW_HEIGHT));
    frame->SetIcons(wxIconBundle("assets/icon.png"));
    frame->Show(true);

    return true;
}