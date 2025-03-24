cmake_minimum_required(VERSION 3.10)
project(Lecture01)

add_executable(Factorial Factorial.cpp)
target_link_libraries(Factorial PRIVATE compiler_flags)

add_executable(Fibonacci Fibonacci.cpp)
target_link_libraries(Fibonacci PRIVATE compiler_flags)

# # check if the executable runs well
# include(CTest)
# add_test(NAME Run_Factorial COMMAND Factorial)
# add_test(NAME Run_Fibonacci COMMAND Fibonacci)
