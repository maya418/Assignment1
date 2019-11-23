cmake_minimum_required(VERSION 3.15)
project(Assignment1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Assignment1
        include/Session.h
        include/json.hpp
        include/User.h
        include/Watchable.h
        src/Main.cpp src/Session.cpp src/Action.cpp src/Watchable.cpp src/User.cpp include/Action.h)
