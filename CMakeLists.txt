CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(googletest)

add_compile_options(-g -O0 -fno-inline)

ADD_EXECUTABLE(spreadsheet main.cpp spreadsheet.cpp)
ADD_EXECUTABLE(test spreadsheet.cpp test.cpp)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
