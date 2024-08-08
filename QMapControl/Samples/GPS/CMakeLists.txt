cmake_minimum_required(VERSION 3.6.0)

find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

if (Qt6Core_FOUND)
        message("Qt6Core found")
	include_directories(${Qt6Test_INCLUDE_DIRS})
	add_definitions(${Qt6Test_DEFINITIONS})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt6Test_EXECUTABLE_COMPILE_FLAGS}")
	set(TEST_LIBRARIES ${Qt6Test_LIBRARIES})
else()
        find_package(Qt5 REQUIRED COMPONENTS Core Network Widgets)
	if (Qt5Test_FOUND)
		message("Qt5Test found")
		include_directories(${Qt5Test_INCLUDE_DIRS})
		add_definitions(${Qt5Test_DEFINITIONS})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Test_EXECUTABLE_COMPILE_FLAGS}")
		set(TEST_LIBRARIES ${Qt5Test_LIBRARIES})
	else()
		message(FATAL_ERROR "Qt5 or Qt6 Test not found")
	endif()
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(GPS REQUIRED libgps)


project(GPSAPP VERSION 1.0
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

add_executable(${PROJECT_NAME}
    ${HEADER_FILES}
    ${SRC_FILES}
)

include(AddFileDependencies)
include(GNUInstallDirs)
include_directories(
    ${GPS_INCLUDE_DIRS}
    ../../src
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${GPS_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${GPS_LIBRARIES}
    libqmapcontrol
)

# Link with Qt libraries
if(Qt6Core_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt6::Core
        Qt6::Network
        Qt6::Widgets
    )
else()
    find_package(Qt5 REQUIRED COMPONENTS Core)
    if(Qt5Core_FOUND)
        target_link_libraries(${PROJECT_NAME} PUBLIC
            Qt5::Core
            Qt5::Network
            Qt5::Widgets
        )
    else()
        message(FATAL_ERROR "Qt5 or Qt6 not found")
    endif()
endif()
