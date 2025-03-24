cmake_minimum_required(VERSION 3.10)
project(Lecture04)

add_executable(UnionFind UnionFind.cpp)
target_link_libraries(UnionFind PRIVATE compiler_flags)

# check if the executable runs well
include(CTest)
add_test(NAME Run_UnionFind COMMAND UnionFind)
