cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME ui_debug) 

project(${PROJECT_NAME} VERSION 0.1)

# Testing
set(ENABLE_TESTING OFF)
# Default 'sets'
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Wx Widgets
set(wxWidgets_USE_STATIC OFF)
set(wxWidgets_USE_UNICODE ON)

if(NOT wxWidgets_USE_STATIC)
message ("Using shared wxWidgets library")
# Default cxx compile and linker flags
set(CXX_FLAGS_WIDGETS_COMPILE "-I/usr/local/lib/wx/include/gtk3-unicode-3.2 -I/usr/local/include/wx-3.2 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXGTK__ -pthread")
set(LINKER_FLAGS_WIDGETS_COMPILE "-L/usr/local/lib -pthread -lwx_gtk3u_xrc-3.2 -lwx_gtk3u_html-3.2 -lwx_gtk3u_qa-3.2 -lwx_gtk3u_core-3.2 -lwx_baseu_xml-3.2 -lwx_baseu_net-3.2 -lwx_baseu-3.2") 
endif()

if (WIN32)
    # Set your own paths
    if(NOT DEFINED ${wxWidgets_ROOT_DIR})
        set(wxDefault_ROOT_DIR "C:\\wxWidgets-3.2.4") 
        message("-DwxWidgets_ROOT_DIR is undefined, set default: ${wxDefault_ROOT_DIR}")
        set(wxWidgets_ROOT_DIR ${wxDefault_ROOT_DIR})
    endif()
    if(NOT DEFINED ${wxWidgets_LIB_DIR})
        set(wxDefault_LIB_DIR "C:\\wxWidgets-3.2.4\\lib\\gcc_lib") 
        message("-DwxWidgets_LIB_DIR is undefined, set default: ${wxDefault_ROOT_DIR}")
        set(wxWidgets_LIB_DIR ${wxDefault_LIB_DIR})
    endif()
endif()

IF(NOT ${CMAKE_BUILD_TYPE} MATCHES "Release")
  SET(CMAKE_BUILD_TYPE "Debug")
ENDIF()

if (WIN32)
    message(STATUS "Make for Windows system")
	# Set debug value if not set release
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        message("--------- CMake Debug build ---------")
        set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/exec/debug)
    else()
        message("--------- CMake Release build ---------")
        set(CMAKE_EXE_LINKER_FLAGS "-static -mwindows")
        set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s")
        set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/exec/release)
    endif()
elseif (UNIX) 
    message(STATUS "Make for Unix system")
    # Take cxxflags for wxWidgets
    message(STATUS "Take cxxflags from wxconfig")
    execute_process(COMMAND wx-config --cxxflags
    RESULT_VARIABLE CommandResult
    OUTPUT_VARIABLE CxxFlagsBuffer)   
    if(CommandResult MATCHES 0)
        string(REPLACE "\n" " " CxxFlagsBuffer ${CxxFlagsBuffer})
        set(CXX_FLAGS_WIDGETS_COMPILE ${CxxFlagsBuffer})
    else()
        message(WARNING "Can\'t take cxx-flags from wx-config. Use default paths.")
    endif()
    # Take libs for wxWidgets
    message(STATUS "Take libs from wxconfig")
    execute_process(COMMAND wx-config --libs
    RESULT_VARIABLE CommandResult
    OUTPUT_VARIABLE LibsBuffer)   
    if(CommandResult MATCHES 0)
        string(REPLACE "\n" " " LibsBuffer ${LibsBuffer})
        set(CMAKE_EXE_LINKER_FLAGS ${LibsBuffer})
    else()
        message(WARNING "Can\'t take libs from wx-config. Use default paths.")
    endif()    
	# Set debug value if not set release
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        message("--------- CMake Debug build ---------")
        set(CMAKE_EXE_LINKER_FLAGS ${LINKER_FLAGS_WIDGETS_COMPILE})
        set(CMAKE_CXX_FLAGS_DEBUG ${CXX_FLAGS_WIDGETS_COMPILE})
        set(CMAKE_CXX_FLAGS_RELEASE ${CXX_FLAGS_WIDGETS_COMPILE})
        set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/exec/debug)
    else()
        message("--------- CMake Release build ---------")

        set(CMAKE_EXE_LINKER_FLAGS ${LINKER_FLAGS_WIDGETS_COMPILE})
        set(CMAKE_CXX_FLAGS_DEBUG  ${CXX_FLAGS_WIDGETS_COMPILE})
        set(CMAKE_CXX_FLAGS_RELEASE ${CXX_FLAGS_WIDGETS_COMPILE})
        set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/exec/release)
    endif()
else ()
	message (FATAL_ERROR "Undefined system")
endif ()

# Sources
set(SOURCES src/main.cpp
 src/frames/MainFrame.cpp src/elements/ParamContainer.cpp src/utility/config.cpp)


# Protocol library
message(STATUS "Add protocol library")
add_subdirectory(libs/FileProtocol)
# Find WxWidgets
message(STATUS "Find wxWidgets library ")
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Add executables
add_executable(${PROJECT_NAME} ${SOURCES})
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}> # Copy assets files
                       )
                  
# Add library
message(STATUS "Linking libraries")
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_link_libraries(${PROJECT_NAME} FileProtocol)

target_include_directories(${PROJECT_NAME} PUBLIC ${wxWidgets_INCLUDE_DIRS})

# Testing
if(${ENABLE_TESTING})
    message(STATUS "--------- Testing is enabled ---------")
    enable_testing()    
endif()    

