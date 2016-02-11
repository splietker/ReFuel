set(CMAKE_AUTOMOC ON)
# Instruct CMake to run rcc automatically (for resources).
set(CMAKE_AUTORCC ON)
find_package(Qt5Widgets)

set(LIB_SOURCE_FILES Notifier.h Notifier.h GammaNotifier.cpp GammaNotifier.h)
set(APP_SOURCE_FILES main.cpp MainWindow.cpp MainWindow.h )
add_library(librefuel ${LIB_SOURCE_FILES})
add_executable(refuel ${APP_SOURCE_FILES} ../refuel.qrc)
target_link_libraries(refuel librefuel Qt5::Widgets)