#include "main.h"
// Implement "main" function for wxWidgets
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MainFrame *frame = new MainFrame(Options::APP_NAME,
                                         wxSize(Options::WINDOW_WIDTH, Options::WINDOW_HEIGHT));
    frame->Show(true);

    return true;
}