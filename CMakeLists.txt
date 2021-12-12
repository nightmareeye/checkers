cmake_minimum_required(VERSION 3.13)
project(test_empty)

set(CMAKE_CXX_STANDART 14)

#sfml

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH}})
find_package(SFML 2.4.2 COMPONENTS graphics audio REQUIRED)
target_link_libraries(chekers sfml-graphics sfml-audio sfml-window sfml-system)
add_executable(chekers main.cpp README.md)