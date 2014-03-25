cmake_minimum_required(VERSION 2.8)
#if you have custom boost installed, please uncomment
#this line with proper boost path
#export BOOST_ROOT=~/usr/boost_1_47_0

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set( CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "Configurations" FORCE )
project( ${SOLUTION_NAME} )
include( environment.cmake required )
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
binaries( boost_mutex_vs_atomic )
find_package(Boost COMPONENTS thread date_time program_options filesystem chrono timer system  REQUIRED)
#find_library(rt REQUIRED)
#add_executable(boost_mutex_vs_atomic)
#target_link_libraries(boost_mutex_vs_atomic rt)
#find_package(rt)
#find_package(Threads)
#TARGET_LINK_LIBRARIES(
#    rt
#)

compile()
