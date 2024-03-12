#pragma once

// Events
namespace AEvents
{
    namespace MainFrameMenuBarIDs
    {
        enum
        {
            appID_PATH_TO_IO = 100,
            appID_NAMES_IO,
            appID_INPUT_FROM_CONTAINERS 
        };
    }
    namespace ParamContainerIDs
    {
        enum
        {
            inpID_TEXT_CTRL = 100,
        };
    }

}

namespace Options
{
    // Files
    constexpr char APP_LOGO_PATH[] = "assets/icon.png";

    // App options
    constexpr char APP_NAME[] = "Dynamics-VR-Debuger"; 
    constexpr int WINDOW_WIDTH = 300;
    constexpr int WINDOW_HEIGHT = 400;
    // App exchange options
    constexpr float EXCHANGE_PER_SECOND = 2;

    // ParamContainer options
    constexpr float PARAM_CONTAINER_DELIM = 0.4;
    constexpr int PARAM_CONTAINER_HEIGHT = 20;
    constexpr int PARAM_BORDER_SIZE = 2;

}