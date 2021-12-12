cmake_minimum_required(VERSION 3.13)
project(checkers)

set(CMAKE_CXX_STANDART 14)
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH}})
find_package(SFML 2.4.2 COMPONENTS graphics audio REQUIRED)

add_executable(checkers Сhecker Сhecker/Checker.h Сhecker/Checkers.cpp Сhecker/Board.h Сhecker/Checkers_on_board.h Сhecker/Game.h Сhecker/Square.h Сhecker/Images Сhecker/Font)

target_link_libraries(checkers sfml-graphics sfml-audio sfml-window sfml-system)