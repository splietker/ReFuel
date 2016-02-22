set(CMAKE_AUTOMOC ON)
# Instruct CMake to run rcc automatically (for resources).
set(CMAKE_AUTORCC ON)
find_package(Qt5Widgets)

SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS log thread system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
find_package(Threads REQUIRED)

set(LIB_SOURCE_FILES Notifier.h Notifier.h BrightnessNotifier.cpp BrightnessNotifier.h Notifier.cpp AmbientLightNotifier.cpp AmbientLightNotifier.h)
set(APP_SOURCE_FILES main.cpp MainWindow.cpp MainWindow.h )
add_library(refuel_lib ${LIB_SOURCE_FILES})
target_link_libraries(refuel_lib m pthread X11 Xrandr ${Boost_LIBRARIES})
add_executable(refuel ${APP_SOURCE_FILES} ../refuel.qrc)
target_link_libraries(refuel refuel_lib Qt5::Widgets)
