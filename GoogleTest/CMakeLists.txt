cmake_minimum_required(VERSION 3.10)

project(UnitTests)

# Locate and add Google Test
find_package(GTest REQUIRED)

add_executable(UnitTests test_PeriodicTask.cpp ../PeriodicTask.cpp)
target_include_directories(UnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(UnitTests PRIVATE GTest::GTest GTest::Main Threads::Threads)

