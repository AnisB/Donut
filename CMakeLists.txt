cmake_minimum_required(VERSION 2.6)
 
project(testStateEngine)


#add_definitions( -DRELEASE )
add_definitions( -DDEBUG )



set(SOURCES "${PROJECT_SOURCE_DIR}/src/")
set(EXTERNAL_LIBS "${PROJECT_SOURCE_DIR}/external/")
set(EXTERNAL_INCLUDES "${PROJECT_SOURCE_DIR}/include/")

IF(WIN32)
set(INCLUDES "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/include")
ELSE()
set(INCLUDES "${PROJECT_SOURCE_DIR}/src")
ENDIF()
set(TEST "${PROJECT_SOURCE_DIR}/test/")



set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")
message(STATUS "${CMAKE_MODULE_PATH}")


file(
	GLOB_RECURSE 
	Source_File 
	${SOURCES}/*.h
	${SOURCES}/*.ih
	${SOURCES}/*.cpp
    )

IF(UNIX AND NOT APPLE)
add_definitions( -D__posix__ )
find_package(OpenGL REQUIRED)
FIND_PACKAGE (glfw REQUIRED)
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARIES})
include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR})
ENDIF()

IF(APPLE)
   FIND_PACKAGE (glfw REQUIRED)
	add_definitions( -D__posix__ )
	add_definitions( -D MACOSX)
   INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(IOKIT_LIBRARY IOKit)
   FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
   MARK_AS_ADVANCED (COCOA_LIBRARY
                     GLFW_LIBRARY
                     OpenGL_LIBRARY
                     IOKIT_LIBRARY)
   SET(CORELIBS ${COCOA_LIBRARY} ${GLFW_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY})
   include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR})

ENDIF (APPLE)

IF(WINDOWS)
add_definitions( -DWIN32 )
ENDIF()

add_library(Donut ${Source_File})
 
link_directories(${CMAKE_BINARY_DIR})

add_subdirectory(${TEST})
	


 


