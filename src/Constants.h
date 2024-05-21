#pragma once
#include <limits>
// Events
namespace AEvents
{
    namespace MainFrameMenuBarIDs
    {
        enum
        {
            appINPUT_PATH_TO_IO = 100,
            appOUTPUT_PATH_TO_IO,
            appREQUEST_ALL_PARAMS, 
            appCHANGE_IO_RATE,
            appENABLE_IO_PROCESS,
            appDISABLE_IO_PROCESS,
            appID_INPUT_FROM_CONTAINERS, 
            appID_ADD_PARAM
        };
    } //namespace MainFrameMenuBarIDs
    namespace ParamContainerIDs
    {
        enum
        {
            inpID_TEXT_CTRL = 100,
        };
    } //namespace ParamContainerIDs
} // namespace AEvents

namespace Options
{
    // Files
    constexpr char APP_LOGO_PATH[] = "icon.png";
    // App options
    constexpr char APP_NAME[] = "Dynamics-VR-Debuger"; 
    constexpr char CONFIG_PATH[] = "config.txt";
    constexpr char LOG_FILE_PATH[] = "log.txt";
    constexpr int WINDOW_WIDTH = 300;
    constexpr int WINDOW_HEIGHT = 400;
    // App exchange options
    constexpr char DEFAULT_IN_FILE_PATH[] = "input.txt";
    constexpr char DEFAULT_OUT_FILE_PATH[] = "output.txt";
    constexpr float EXCHANGE_PER_SECOND = 30;
    // ParamContainer options
    constexpr float PARAM_CONTAINER_DELIM = 0.4;
    constexpr int PARAM_CONTAINER_HEIGHT = 20;
    constexpr int PARAM_BORDER_SIZE = 2;
    constexpr double PARAM_INCREMENT_VALUE = 5;
    constexpr double PARAM_MAX_VALUE = std::numeric_limits<double>().max();
} // namespace Options