cmake_minimum_required(VERSION 3.15)
project(Assingment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Assingment1
        include/Action.h
        include/json.hpp
        include/Session.h
        include/User.h
        include/Watchable.h
        src/Action.cpp
        src/Main.cpp
        src/Session.cpp
        src/User.cpp
        src/Watchable.cpp)
