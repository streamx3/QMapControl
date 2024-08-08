cmake_minimum_required(VERSION 3.6.0)

project(QMapControlRepo VERSION 1.0
  DESCRIPTION "Qt Map Widget"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_subdirectory(QMapControl/src)
add_subdirectory(QMapControl/Samples)


