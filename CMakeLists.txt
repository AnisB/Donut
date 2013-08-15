cmake_minimum_required(VERSION 2.6)
 
project(testStateEngine)


#add_definitions( -DRELEASE )
add_definitions( -DDEBUG )
add_definitions( -D__posix__ )

set(SOURCES "${PROJECT_SOURCE_DIR}/src/")
set(INCLUDES ../src)
set(TEST "${PROJECT_SOURCE_DIR}/test/")

file(
	GLOB_RECURSE 
	Source_File 
	${SOURCES}/*.h
	${SOURCES}/*.ih
	${SOURCES}/*.cpp
    )
 
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARIES})
include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_library(Donut ${Source_File})
 
link_directories(${CMAKE_BINARY_DIR})

add_subdirectory(${TEST})
	


 


