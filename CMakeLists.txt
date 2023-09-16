cmake_minimum_required(VERSION 3.26)
project(Space_traffic)

set(CMAKE_CXX_STANDARD 20)

add_executable(Space_traffic main.cpp
        Deflector.h
        Ship.h
        ShipConstants.h
        Engine.h
        EngineConstants.h
        DeflectorConstants.h
        Difficulties.h
        GetDamage.cpp)
