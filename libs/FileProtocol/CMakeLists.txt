cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME FileProtocol)

project(${PROJECT_NAME})

# os specific sources
if(WIN32)
    set(OS_FOLDER Windows)
elseif(UNIX)
    set(OS_FOLDER Unix)
endif()

file(GLOB OS_SPECIFIC src/${OS_FOLDER}/*)


set(SOURCES 
    include/FileProtocol.h 
    src/FileProtocol.cpp
    ${OS_SPECIFIC}
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/${OS_FOLDER})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
