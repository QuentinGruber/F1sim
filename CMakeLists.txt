cmake_minimum_required(VERSION 3.15)
project(proj_c)

set(CMAKE_CXX_STANDARD 20)

add_executable(proj_c main.cpp Classes/Cars.cpp Classes/Cars.h Classes/Race.cpp Classes/Race.h Classes/Circuit.cpp Classes/Circuit.h Classes/Cars_bot.cpp Classes/Cars_bot.h Classes/utils.cpp Classes/utils.h)