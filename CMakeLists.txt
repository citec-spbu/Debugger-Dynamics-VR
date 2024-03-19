cmake_minimum_required(VERSION 3.7)

set(PROJECT_NAME PCTP) 

project(${PROJECT_NAME} VERSION 0.12)

add_executable(${PROJECT_NAME} PCTP.cpp)

add_library(SRC data_tools.h data_tools.cpp file_tools.h file_tools.cpp lib_mac.h)
target_link_libraries(${PROJECT_NAME} SRC)