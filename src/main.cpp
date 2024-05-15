#include "Main.h"
#include <ctime>
#include <thread>

// Implement "main" function for wxWidgets
IMPLEMENT_APP(MyApp)

BEGIN_EVENT_TABLE(MyApp, wxApp)
EVT_IDLE(MyApp::onIdle)
END_EVENT_TABLE()

static std::ofstream log_file(Options::LOG_FILE_PATH, std::ios::trunc | std::ios::out);

bool MyApp::OnInit() 
{
    wxInitAllImageHandlers();    
    delete wxLog::SetActiveTarget(new wxLogStream(&log_file));
    frame = new MainFrame(Options::APP_NAME,
                                         wxSize(Options::WINDOW_WIDTH, Options::WINDOW_HEIGHT));
    frame->SetIcons(wxIconBundle(Options::APP_LOGO_PATH));
    frame->Show(true);  
    return true;
}

void MyApp::onIdle(wxIdleEvent& evt)
{
    using namespace std::chrono;

    // prevent high cpu usage
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // Calculate delta time
    static steady_clock::time_point last_time = steady_clock::now();
    steady_clock::time_point time = steady_clock::now();
    float deltaTime = duration_cast<milliseconds>(time - last_time).count();
    last_time = time;

    if(!evt.MoreRequested())
    {
        evt.RequestMore();
    }

    frame->processIO(deltaTime);
}   