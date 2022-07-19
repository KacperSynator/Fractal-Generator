cmake_minimum_required(VERSION 3.10)

project(fractal-generator CXX) 

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cc")
file(GLOB HEADERS "inc/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
