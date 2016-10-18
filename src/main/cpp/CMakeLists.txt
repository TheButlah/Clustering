

#Helper variable for all the source files
set(DBSCAN_FILES
    DBSCAN.cpp
    Point3D.cpp
    OccupancyGrid.cpp)

add_library(dbscan ${DBSCAN_FILES})
add_executable(demo main.cpp)

target_include_directories(dbscan PUBLIC include)
target_link_libraries(demo dbscan)
#copy the demo executable to the resources directory in build
add_custom_command(TARGET demo
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:demo> "${CMAKE_BINARY_DIR}/res")
