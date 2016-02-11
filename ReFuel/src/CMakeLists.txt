set(CMAKE_AUTOMOC ON)
# Instruct CMake to run rcc automatically (for resources).
set(CMAKE_AUTORCC ON)
find_package(Qt5Widgets)

set(SOURCE_FILES main.cpp MainWindow.cpp MainWindow.h Notifier.h Notifier.h)
add_executable(refuel ${SOURCE_FILES} ../refuel.qrc)
target_link_libraries(refuel Qt5::Widgets)