cmake_minimum_required(VERSION 2.6)
project (largeFileSorting LANGUAGES CXX)

find_package(GTest REQUIRED)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -lgtest")
SET(SRC_LIST_CF CreateFile/CreateFile.cpp)
SET(SRC_LIST_FS FileSorting/main.cpp FileSorting/SortingFunctions.cpp FileSorting/SortingFunctions.h)
SET(SRC_LIST_TESTS Tests/CorrectTest.cpp FileSorting/SortingFunctions.cpp FileSorting/SortingFunctions.h)

include_directories(${GTEST_INCLUDE_DIR})
include_directories(./FileSorting)

add_executable(FileSorting ${SRC_LIST_FS})
add_executable(CreateFile ${SRC_LIST_CF})
add_executable(CorrectTest ${SRC_LIST_TESTS})

target_link_libraries(CorrectTest ${GTEST_LIBRARIES})

enable_testing()
add_test(CorrectTest CorrectTest)