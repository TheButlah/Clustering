add_library (Dbscan DBSCAN.cpp DBSCAN.h Point3D.hpp Point3D.cpp )
add_executable (demo main.cpp)
target_link_libraries (demo Sqr)