cmake_minimum_required(VERSION 3.10)
project(Lecture03)

add_executable(Stack Stack.cpp)
target_link_libraries(Stack PRIVATE compiler_flags)

# check if the executable runs well
include(CTest)
add_test(NAME Run_Stack COMMAND Stack)
