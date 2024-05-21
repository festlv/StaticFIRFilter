cmake_minimum_required(VERSION 3.23.1)

set(NAME StaticFIRFilter)
project(${NAME})

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        CppUTest
        GIT_REPOSITORY      https://github.com/cpputest/cpputest.git
        GIT_TAG             master
)
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(CppUTest)

set(SRC
        main.cpp
        StaticFIRFilter.hpp
        test.cpp)


add_executable(${NAME} ${SRC})
target_link_libraries(${NAME} PRIVATE
        CppUTest::CppUTest)
target_include_directories(${NAME} PUBLIC "StaticCircularBuffer/")
