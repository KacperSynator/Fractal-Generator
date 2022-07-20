cmake_minimum_required(VERSION 3.10)

project(fractal-generator CXX) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SOURCES "*.cc")
file(GLOB_RECURSE HEADERS "*.h")

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME} ${SOURCES} gui/main_window.ui gui/resources.qrc)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}/inc/image"
    "${PROJECT_SOURCE_DIR}/inc/fractal"
    "${PROJECT_SOURCE_DIR}/gui")
