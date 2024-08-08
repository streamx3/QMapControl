cmake_minimum_required(VERSION 3.6.0)

project(GPS VERSION 1.0
  DESCRIPTION "GPS Test App"
  LANGUAGES CXX
)

set(SRC_FILES
    src/main.cpp
    src/gpsclient.cpp
    src/gps.cpp
)

set(HEADER_FILES
    src/gpsclient.h
    src/gps.h
)
