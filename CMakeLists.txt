cmake_minimum_required(VERSION 3.1)
project(CLOptParser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -DDEBUG -pedantic")
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ROOT "/usr/local/include/boost")

find_package(Boost COMPONENTS log unit_test_framework REQUIRED)

if(Boost_FOUND)
    add_definitions("-DBOOST_LOG_DYN_LINK")
    link_directories(${Boost_LIBRARY_DIR})
    include_directories(${Boost_INCLUDE_DIR})
endif()

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(TESTS_DIR "${PROJECT_SOURCE_DIR}/tests")
set(SOURCE_FILES ${SOURCE_DIR}/optgroup.cpp ${SOURCE_DIR}/option.cpp ${SOURCE_DIR}/optparser.cpp)
set(HEADER_FILES ${SOURCE_DIR}/option.hpp ${SOURCE_DIR}/optparser.hpp ${SOURCE_DIR}/optgroup.hpp ${SOURCE_DIR}/opexception.hpp)

add_library(clop SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(clop ${Boost_LOG_LIBRARIES})

add_executable(BasicTest ${TESTS_DIR}/basic.cpp)
target_link_libraries(BasicTest ${Boost_LOG_LIBRARIES} clop)

add_executable(OptionsTest ${TESTS_DIR}/unit/optiontest.cpp)
target_link_libraries(OptionsTest ${Boost_LOG_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORD_LIBRARIES} clop)