# Include common configurations
set(CMAKE_CXX_STANDARD 11)

# Define the target name based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(TARGET_NAME qmapcontrold)
else()
    set(TARGET_NAME qmapcontrol)
endif()

# Define the target library
add_library(${TARGET_NAME} SHARED
    Geometry.cpp
    GeometryLineString.cpp
    GeometryPoint.cpp
    GeometryPointShape.cpp
    GeometryPointShapeScaled.cpp
    GeometryPointArrow.cpp
    GeometryPointCircle.cpp
    GeometryPointImage.cpp
    GeometryPointImageScaled.cpp
    GeometryPolygon.cpp
    GeometryPolygonImage.cpp
    GeometryWidget.cpp
    GPS_Position.cpp
    ImageManager.cpp
    Layer.cpp
    LayerGeometry.cpp
    LayerMapAdapter.cpp
    MapAdapter.cpp
    MapAdapterGoogle.cpp
    MapAdapterBing.cpp
    MapAdapterOSM.cpp
    MapAdapterOTM.cpp
    MapAdapterTile.cpp
    MapAdapterWMS.cpp
    MapAdapterYahoo.cpp
    NetworkManager.cpp
    Projection.cpp
    ProjectionEquirectangular.cpp
    ProjectionSphericalMercator.cpp
    QMapControl.cpp
    QProgressIndicator.cpp
)

# Add the header files
target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Define required defines
target_compile_definitions(${TARGET_NAME} PUBLIC
    QT_NO_DEBUG_OUTPUT
    _USE_MATH_DEFINES
    _VARIADIC_MAX=6
    QMAPCONTROL_LIBRARY
)

find_package(Qt6 QUIET COMPONENTS Core)
# Link with Qt libraries
if(Qt6Core_FOUND)
    target_link_libraries(${TARGET_NAME} PUBLIC
        Qt6::Core
        # Qt6::Network
        Qt6::Widgets
    )
else()
    find_package(Qt5 REQUIRED COMPONENTS Core)
    if(Qt5Core_FOUND)
        target_link_libraries(${TARGET_NAME} PUBLIC
            Qt5::Core
            # Qt5::Network
            Qt5::Widgets
        )
    else()
        message(FATAL_ERROR "Qt5 or Qt6 not found")
    endif()
endif()

# Conditional GDAL support
if(QMC_GDAL)
    message(STATUS "Building with GDAL support...")

    target_sources(${TARGET_NAME} PRIVATE
        ESRIShapefile.cpp
        LayerESRIShapefile.cpp
    )

    target_include_directories(${TARGET_NAME} PRIVATE
        ${QMC_GDAL_INC}
    )

    target_link_libraries(${TARGET_NAME} PRIVATE
        ${QMC_GDAL_LIB}
        gdal
    )
endif()

# Installation settings
set_target_properties(${TARGET_NAME} PROPERTIES VERSION 1.0.0)

install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES
    qmapcontrol_global.h
    Geometry.h
    GeometryLineString.h
    GeometryPoint.h
    GeometryPointShape.h
    GeometryPointShapeScaled.h
    GeometryPointArrow.h
    GeometryPointCircle.h
    GeometryPointImage.h
    GeometryPointImageScaled.h
    GeometryPolygon.h
    GeometryPolygonImage.h
    GeometryWidget.h
    GPS_Position.h
    ImageManager.h
    Layer.h
    LayerGeometry.h
    LayerMapAdapter.h
    MapAdapter.h
    MapAdapterGoogle.h
    MapAdapterBing.h
    MapAdapterOSM.h
    MapAdapterOTM.h
    MapAdapterTile.h
    MapAdapterWMS.h
    MapAdapterYahoo.h
    NetworkManager.h
    Point.h
    Projection.h
    ProjectionEquirectangular.h
    ProjectionSphericalMercator.h
    QMapControl.h
    QuadTreeContainer.h
    QProgressIndicator.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/QMapControl
)
