cmake_minimum_required(VERSION 3.2)
project(Clustering)

#Enable c++11 and print more warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

#Tell cmake where to put the executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

#tell cmake to look at CMakeLists.txt in these dirs
add_subdirectory(src/main/cpp)
#add_subdirectory(src/test/cpp)

#copy resources to build/res
file(COPY src/main/res DESTINATION .)

#copy include headers to build/include
file(COPY src/main/cpp/include DESTINATION .)



#enable_testing()
#add_test(NAME MyTest COMMAND Test)
