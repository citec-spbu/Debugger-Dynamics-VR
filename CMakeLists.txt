cmake_minimum_required(VERSION 3.7)

set(PROJECT_NAME ui_debug) 

# Default 'sets'
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set your own paths
set(wxWidgets_ROOT_DIR "C:/Program Files (x86)/wxWidgets")
set(wxWidgets_LIB_DIR "C:/Program Files (x86)/wxWidgets/lib/gcc_x64_dll")

# Sources
set(SOURCES src/Main.cpp src/frames/MainFrame.cpp)

project(${PROJECT_NAME} VERSION 0.1)

# Find WxWidgets
find_package(wxWidgets REQUIRED COMPONENTS net core base)

# Add executables
add_executable(${PROJECT_NAME} ${SOURCES})

# Add library
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${wxWidgets_INCLUDE_DIRS})
