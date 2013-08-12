cmake_minimum_required(VERSION 2.6)
 
project(testStateEngine)


add_definitions( -DDEBUG )
add_definitions( -D__posix__ )

set(SOURCES "${PROJECT_SOURCE_DIR}/src/")
set(INCLUDES ../src)

file(
	GLOB_RECURSE 
	Source_File 
	${SOURCES}/*.h
	${SOURCES}/*.ih
	${SOURCES}/*.cpp
    )
 

add_definitions(-DDEBUG)
include_directories(${SOURCES})

add_library(Donut ${Source_File})
 
link_directories(${CMAKE_BINARY_DIR})
#  SFML finding
add_executable(testStateEngine main.cpp)
TARGET_LINK_LIBRARIES(testStateEngine Donut)

	


 


