find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

enable_testing()

add_executable(notifier_test BrightnessNotifierTest.cpp AmbientLightNotifierTest.cpp)
target_link_libraries(notifier_test ${GTEST_BOTH_LIBRARIES} refuel_lib)