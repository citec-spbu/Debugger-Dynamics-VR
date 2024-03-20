cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME FileProtocol)

project(${PROJECT_NAME})

set(SOURCES 
    include/FileProtocol.h 
    src/FileProtocol.cpp
    auxiliary/file_tools.h
    auxiliary/file_tools.cpp
    auxiliary/data_tools.h
    auxiliary/data_tools.cpp
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/auxiliary)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)