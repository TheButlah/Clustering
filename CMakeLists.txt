cmake_minimum_required(VERSION 3.2)
project(Clustering)

#tell cmake to look at CMakeLists.txt in these dirs
add_subdirectory(src/main/cpp)
#add_subdirectory(src/test/cpp)

#copy resources to build/res
file(COPY src/main/res DESTINATION .)

#copy include headers to build/include
file(COPY src/main/cpp/include DESTINATION .)



#enable_testing()
#add_test(NAME MyTest COMMAND Test)
