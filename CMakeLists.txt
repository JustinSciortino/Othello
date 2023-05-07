cmake_minimum_required(VERSION 3.23)
project(Assignment2)

set(CMAKE_CXX_STANDARD 17)
set(Headers Game.h Player.h Board.h Position.h UnplayablePosition.h PlayablePosition.h)
add_executable(Assignment2 main.cpp Game.h Game.cpp Board.h Board.cpp Position.h Position.cpp Player.h Player.cpp PlayablePosition.h PlayablePosition.cpp UnplayablePosition.h UnplayablePosition.cpp)
#add_executable(Assignment2 main.cpp Game.h Game.cpp Board.h Board.cpp Position.h Position.cpp Player.h Player.cpp PlayablePosition.h PlayablePosition.cpp)
#add_executable(main.cpp Game.h Game.cpp Board.h Board.cpp Position.h Position.cpp Player.h Player.cpp PlayablePosition.h PlayablePosition.cpp UnplayablePosition.h UnplayablePosition.cpp)