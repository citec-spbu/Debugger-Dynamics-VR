cmake_minimum_required(VERSION 3.7)

set(PROJECT_NAME ui_debug) 

project(${PROJECT_NAME} VERSION 0.1)

# Testing
set(ENABLE_TESTING OFF)
# Default 'sets'
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set your own paths
set(wxWidgets_ROOT_DIR "C:/Program Files (x86)/wxWidgets")
set(wxWidgets_LIB_DIR "C:/Program Files (x86)/wxWidgets/lib/gcc_x64_dll")
set(BOOST_ROOT "C:/Program Files (x86)/Boost")
# Sources
set(SOURCES src/Main.cpp
 src/frames/MainFrame.cpp src/elements/ParamContainer.cpp src/utility/protocol.cpp src/utility/config.cpp)



# Find Boost
find_package(Boost REQUIRED) 
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
# Find WxWidgets
find_package(wxWidgets REQUIRED COMPONENTS net core base)



# Add executables
add_executable(${PROJECT_NAME} ${SOURCES})

# Add library
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${wxWidgets_INCLUDE_DIRS})

# Testing
if(${ENABLE_TESTING})
    enable_testing()

    # Test Protocol 
    add_executable(test_protocol src/utility/test_protocol.cpp src/utility/protocol.cpp)
    target_link_libraries(test_protocol ${Boost_LIBRARIES})
    target_include_directories(test_protocol PUBLIC ${Boost_INCLUDE_DIRS})
    add_test(TestProtocol test_protocol)
endif()    
