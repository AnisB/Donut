cmake_minimum_required(VERSION 2.6)
 
project(Donut)


#add_definitions( -DRELEASE )
add_definitions( -DDEBUG )



set(SOURCES "${PROJECT_SOURCE_DIR}/src/")

IF(UNIX AND NOT APPLE)
set(EXTERNAL_LIBS "${PROJECT_SOURCE_DIR}/external/linux")
set(EXTERNAL_INCLUDES "${PROJECT_SOURCE_DIR}/include/linux")
ENDIF()

IF(APPLE)
set(EXTERNAL_LIBS "${PROJECT_SOURCE_DIR}/external/mac")
set(EXTERNAL_INCLUDES "${PROJECT_SOURCE_DIR}/include/mac")
ENDIF()

set(TEST "${PROJECT_SOURCE_DIR}/test/")
set(PROGRAM "${PROJECT_SOURCE_DIR}/program/")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")


file(
	GLOB_RECURSE 
	Source_File 
	${SOURCES}/*.h
	${SOURCES}/*.ih
	${SOURCES}/*.cpp
    )

IF(UNIX AND NOT APPLE)
add_definitions( -D__posix__ )
add_definitions( -D LINUX )
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
FIND_PACKAGE (X11 REQUIRED)
set(GRAPHIC_LIBS "${EXTERNAL_LIBS}/libglfw3.a" ${GLEW_LIBRARY} ${OPENGL_LIBRARIES} 
 ${X11_Xxf86vm_LIB} ${X11_Xrandr_LIB} ${X11_Xi_LIB} pthread)
   SET(IMAGE_LIBS jpeg png)
   SET(CORELIBS ${GRAPHIC_LIBS} ${IMAGE_LIBS})
include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${EXTERNAL_LIBS} )
ENDIF()

IF(APPLE)
  add_definitions( -DMACOSX)
  add_definitions( -D__posix__ )
  INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  FIND_LIBRARY(IOKIT_LIBRARY IOKit)
  FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
  find_package(GLEW REQUIRED)
  MARK_AS_ADVANCED (COCOA_LIBRARY
                   GLFW_LIBRARY
                   OpenGL_LIBRARY
                   IOKIT_LIBRARY)
  SET(GRAPHIC_LIBS ${COCOA_LIBRARY} ${GLEW_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} "${EXTERNAL_LIBS}/libglfw3.a")
  SET(IMAGE_LIBS jpeg png)
  SET(CORELIBS ${GRAPHIC_LIBS} ${IMAGE_LIBS})
  include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${EXTERNAL_LIBS})
ENDIF (APPLE)

IF(WINDOWS)
add_definitions( -DWIN32 )
ENDIF()

add_library(Donut ${Source_File})
 
link_directories(${CMAKE_BINARY_DIR})

add_subdirectory(${TEST})
add_subdirectory(${PROGRAM})


add_custom_command(
    TARGET Donut POST_BUILD
    COMMAND ln -sf ${PROJECT_SOURCE_DIR}/data/shaders ${PROJECT_BINARY_DIR}
)

add_custom_command(
    TARGET Donut POST_BUILD
    COMMAND ln -sf ${PROJECT_SOURCE_DIR}/data ${PROJECT_BINARY_DIR}
)
  
add_custom_command(
    TARGET Donut POST_BUILD
    COMMAND ln -sf ${PROJECT_SOURCE_DIR}/models ${PROJECT_BINARY_DIR}
)


 


