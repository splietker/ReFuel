cmake_minimum_required(VERSION 3.3)
project(ReFuel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_AUTOMOC ON)
# Instruct CMake to run rcc automatically (for resources).
set(CMAKE_AUTORCC ON)
find_package(Qt5Widgets)

set(SOURCE_FILES main.cpp MainWindow.cpp MainWindow.h)
add_executable(refuel ${SOURCE_FILES} refuel.qrc)
target_link_libraries(refuel Qt5::Widgets)
