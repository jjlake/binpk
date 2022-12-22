# CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(binpk CXX)
add_executable(binpk main.cpp File.cpp Group.cpp Output.cpp Sort.cpp options.cpp util.cpp)
set_property(TARGET binpk PROPERTY CXX_STANDARD 20)

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests test.cpp File.cpp Group.cpp Output.cpp Sort.cpp options.cpp util.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
set_property(TARGET tests PROPERTY CXX_STANDARD 20)
