cmake_minimum_required(VERSION 3.26)
project(Space_traffic)

set(CMAKE_CXX_STANDARD 20)

include_directories(Src)

add_executable(Space_traffic Src/main.cpp
        Src/Deflector.h
        Src/Ship.h
        Src/ShipConstants.h
        Src/Engine.h
        Src/EngineConstants.h
        Src/DeflectorConstants.h
        Src/Difficulties.h
        Src/Result.h
        Src/Damage.h
        Src/Conditions.h
        Src/Market.h
        Src/Test.cpp
        Src/Test.h
        Src/IsTypeChecker.h)
