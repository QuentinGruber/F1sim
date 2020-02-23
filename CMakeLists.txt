cmake_minimum_required(VERSION 3.15)
project(F1sim)

set(CMAKE_CXX_STANDARD 20)

add_executable(F1sim main.cpp Classes/Cars.cpp Classes/Cars.h Classes/Race.cpp Classes/Race.h Classes/Circuit.cpp Classes/Circuit.h Classes/Cars_bot.cpp Classes/Cars_bot.h Classes/utils.cpp Classes/utils.h)