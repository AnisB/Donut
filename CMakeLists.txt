cmake_minimum_required(VERSION 2.6)
 
project(testStateEngine)


#add_definitions( -DRELEASE )
add_definitions( -DDEBUG )

set(SOURCES "${PROJECT_SOURCE_DIR}/src/")

IF(WIN32)
set(INCLUDES "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/include")
ELSE()
set(INCLUDES "${PROJECT_SOURCE_DIR}/src")
ENDIF()
set(TEST "${PROJECT_SOURCE_DIR}/test/")

file(
	GLOB_RECURSE 
	Source_File 
	${SOURCES}/*.h
	${SOURCES}/*.ih
	${SOURCES}/*.cpp
    )

IF(UNIX)
add_definitions( -D__posix__ )
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARIES})
include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
ELSE()
add_definitions( -DWIN32 )
ENDIF()

add_library(Donut ${Source_File})
 
link_directories(${CMAKE_BINARY_DIR})

add_subdirectory(${TEST})
	


 


