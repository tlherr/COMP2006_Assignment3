cmake_minimum_required(VERSION 3.7)
project(COMP2006_Assignment3)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Cards.h Deck.h Hand.h Player.h Game.h Cribbage.h)
add_executable(COMP2006_Assignment3 ${SOURCE_FILES})