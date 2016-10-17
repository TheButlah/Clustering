#Enable c++11 and print more warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

#Tell cmake where to put the executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

#Helper variable for all the source files
set(DBSCAN_FILES
    DBSCAN.cpp
    Point3D.cpp
        )

add_library(dbscan ${DBSCAN_FILES})
add_executable(demo main.cpp)

target_include_directories(dbscan PUBLIC include)
target_link_libraries(demo dbscan)
#copy the demo executable to the resources directory in build
add_custom_command(TARGET demo
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:demo> "${CMAKE_BINARY_DIR}/res")
