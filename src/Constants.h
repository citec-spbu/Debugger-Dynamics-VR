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
            appID_INPUT_FROM_CONTAINERS, 
            appID_ADD_PARAM
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
    constexpr char CONFIG_PATH[] = "config.txt";
    constexpr char LOG_FILE_PATH[] = "log.txt";
    constexpr int WINDOW_WIDTH = 300;
    constexpr int WINDOW_HEIGHT = 400;
    // App exchange options
    constexpr char DEFAULT_IN_FILE_PATH[] = "input.txt";
    constexpr char DEFAULT_OUT_FILE_PATH[] = "output.txt";
    constexpr float EXCHANGE_PER_SECOND = 2;

    // ParamContainer options
    constexpr float PARAM_CONTAINER_DELIM = 0.4;
    constexpr int PARAM_CONTAINER_HEIGHT = 20;
    constexpr int PARAM_BORDER_SIZE = 2;

}