cmake_minimum_required(VERSION 3.10)

project(QMapControl LANGUAGES CXX)


find_package(Qt6 QUIET COMPONENTS Core)

if(Qt6Core_FOUND)
    message("Qt6 found")
    include_directories(${Qt6Core_INCLUDE_DIRS})
    add_definitions(${Qt6Core_DEFINITIONS})
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    set(PC_Requires "Qt6Core")
else()
    find_package(Qt5 REQUIRED COMPONENTS Core)

    if(Qt5Core_FOUND)
        message("Qt5 found")
        include_directories(${Qt5Core_INCLUDE_DIRS})
        add_definitions(${Qt5Core_DEFINITIONS})
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
        set(CMAKE_AUTOMOC ON)
        set(CMAKE_AUTORCC ON)
        set(CMAKE_AUTOUIC ON)
        set(PC_Requires "Qt5Core")
    else()
        message(FATAL_ERROR "Qt5 or Qt6 not found")
    endif()
endif()

if(Qt6Core_FOUND)
    find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
else()
    find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
endif()

find_package(PkgConfig REQUIRED)

# Define the Qt version
if (DEFINED ENV{QT_VERSION} AND "$ENV{QT_VERSION}" STREQUAL "6")
    set(QT_VERSION_MAJOR 6)
else()
    set(QT_VERSION_MAJOR 5)
endif()


# add_subdirectory(lib)
add_subdirectory(QMapControl/Samples)
add_subdirectory(QMapControl/src)


