cmake_minimum_required(VERSION 3.6.0)

project(libqmapcontrol VERSION 1.0
  DESCRIPTION "QMapControl library"
  LANGUAGES CXX
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(PkgConfig REQUIRED)

set(SRC_FILES
    QMapControl/Geometry.cpp
    QMapControl/GeometryLineString.cpp
    QMapControl/GeometryPoint.cpp
    QMapControl/GeometryPointShape.cpp
    QMapControl/GeometryPointShapeScaled.cpp
    QMapControl/GeometryPointArrow.cpp
    QMapControl/GeometryPointCircle.cpp
    QMapControl/GeometryPointImage.cpp
    QMapControl/GeometryPointImageScaled.cpp
    QMapControl/GeometryPolygon.cpp
    QMapControl/GeometryPolygonImage.cpp
    QMapControl/GeometryWidget.cpp
    QMapControl/GPS_Position.cpp
    QMapControl/ImageManager.cpp
    QMapControl/Layer.cpp
    QMapControl/LayerGeometry.cpp
    QMapControl/LayerMapAdapter.cpp
    QMapControl/MapAdapter.cpp
    QMapControl/MapAdapterGoogle.cpp
    QMapControl/MapAdapterBing.cpp
    QMapControl/MapAdapterOSM.cpp
    QMapControl/MapAdapterOTM.cpp
    QMapControl/MapAdapterTile.cpp
    QMapControl/MapAdapterWMS.cpp
    QMapControl/MapAdapterYahoo.cpp
    QMapControl/NetworkManager.cpp
    QMapControl/Projection.cpp
    QMapControl/ProjectionEquirectangular.cpp
    QMapControl/ProjectionSphericalMercator.cpp
    QMapControl/QMapControl.cpp
    QMapControl/QProgressIndicator.cpp
)

set(HEADER_FILES
    QMapControl/qmapcontrol_global.h
    QMapControl/Geometry.h
    QMapControl/GeometryLineString.h
    QMapControl/GeometryPoint.h
    QMapControl/GeometryPointShape.h
    QMapControl/GeometryPointShapeScaled.h
    QMapControl/GeometryPointArrow.h
    QMapControl/GeometryPointCircle.h
    QMapControl/GeometryPointImage.h
    QMapControl/GeometryPointImageScaled.h
    QMapControl/GeometryPolygon.h
    QMapControl/GeometryPolygonImage.h
    QMapControl/GeometryWidget.h
    QMapControl/GPS_Position.h
    QMapControl/ImageManager.h
    QMapControl/Layer.h
    QMapControl/LayerGeometry.h
    QMapControl/LayerMapAdapter.h
    QMapControl/MapAdapter.h
    QMapControl/MapAdapterGoogle.h
    QMapControl/MapAdapterBing.h
    QMapControl/MapAdapterOSM.h
    QMapControl/MapAdapterOTM.h
    QMapControl/MapAdapterTile.h
    QMapControl/MapAdapterWMS.h
    QMapControl/MapAdapterYahoo.h
    QMapControl/NetworkManager.h
    QMapControl/Point.h
    QMapControl/Projection.h
    QMapControl/ProjectionEquirectangular.h
    QMapControl/ProjectionSphericalMercator.h
    QMapControl/QMapControl.h
    QMapControl/QuadTreeContainer.h
    QMapControl/QProgressIndicator.h
)

add_library(${PROJECT_NAME}
    ${HEADER_FILES}
    ${SRC_FILES}
)

target_link_libraries(${PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Core
)

include_directories(
    ${GPS_INCLUDE_DIRS}
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
