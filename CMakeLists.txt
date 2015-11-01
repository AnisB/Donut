cmake_minimum_required(VERSION 2.6)
 
project(DonutEngine)

MACRO(GENERATE_LIB LIB_PATH LIB_NAME)
  SET(${Source_File} "")
file(
  GLOB_RECURSE 
  Source_File 
  ${LIB_PATH}/*.h
  ${LIB_PATH}/*.ih
  ${LIB_PATH}/*.cpp
    )
add_library(${LIB_NAME} ${Source_File})
include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${EXTERNAL_LIBS} )
ENDMACRO()




#add_definitions( -D_RELEASE )
add_definitions( -D_DEBUG )

# Setting the compiler data
add_definitions(-std=c++11) 
set(CMAKE_BUILD_TYPE "Debug")
IF (NOT WIN32)
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")
ENDIF()
link_directories(${CMAKE_BINARY_DIR})

# Setting the folder data
set(SOURCES "${PROJECT_SOURCE_DIR}/src/")
set(TEST "${PROJECT_SOURCE_DIR}/test/")
set(PROGRAM "${PROJECT_SOURCE_DIR}/program/")

# Setting the include and external includes and data
IF(UNIX AND NOT APPLE)
set(EXTERNAL_LIBS "${PROJECT_SOURCE_DIR}/external/linux")
set(EXTERNAL_INCLUDES "${PROJECT_SOURCE_DIR}/include/linux")
ENDIF()
IF(APPLE)
set(EXTERNAL_LIBS "${PROJECT_SOURCE_DIR}/external/mac")
set(EXTERNAL_INCLUDES "${PROJECT_SOURCE_DIR}/include/mac")
ENDIF()
IF(WIN32)
set(EXTERNAL_LIBS "${PROJECT_SOURCE_DIR}/external/windows")
set(EXTERNAL_INCLUDES "${PROJECT_SOURCE_DIR}/include/windows")
ENDIF()

# Setting the needs
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
ENDIF (APPLE)

IF(WIN32)
add_definitions( -DWIN32 )
FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
SET(GRAPHIC_LIBS "${EXTERNAL_LIBS}/lib-vc2012/glfw3.lib" "${EXTERNAL_LIBS}/glew32.lib" "${EXTERNAL_LIBS}/glew32s.lib" "opengl32.lib")
SET(CORELIBS ${GRAPHIC_LIBS} )
ENDIF()

# Generating the libraries
GENERATE_LIB("${SOURCES}/base" Base)
GENERATE_LIB("${SOURCES}/butter" Butter)
GENERATE_LIB("${SOURCES}/engine" Engine)
GENERATE_LIB("${SOURCES}/input" Input)
GENERATE_LIB("${SOURCES}/multithread" MultiThread)
GENERATE_LIB("${SOURCES}/objects" Objects)
GENERATE_LIB("${SOURCES}/render" Render)
GENERATE_LIB("${SOURCES}/core" Core)
GENERATE_LIB("${SOURCES}/graphics" Graphics)
GENERATE_LIB("${SOURCES}/resource" Resource)
GENERATE_LIB("${SOURCES}/stateengine" StateEngine)
GENERATE_LIB("${SOURCES}/tools" Tools)
GENERATE_LIB("${SOURCES}/tracing" Tracing)

SET(CORELIBS ${CORELIBS} Base Butter Engine Input Core MultiThread Objects Render Graphics Resource StateEngine Tools Tracing)

# Adding the tests if we should
IF(TESTS)
add_subdirectory(${TEST})
ENDIF()

# Adding the programs if we should
add_subdirectory(${PROGRAM})


# Adding the links on linux and mac
IF(UNIX)
add_custom_command(
    TARGET Tracing POST_BUILD
    COMMAND ln -sf ${PROJECT_SOURCE_DIR}/data/shaders ${PROJECT_BINARY_DIR}
)

add_custom_command(
    TARGET Tracing POST_BUILD
    COMMAND ln -sf ${PROJECT_SOURCE_DIR}/data ${PROJECT_BINARY_DIR}
)
  
add_custom_command(
    TARGET Tracing POST_BUILD
    COMMAND ln -sf ${PROJECT_SOURCE_DIR}/models ${PROJECT_BINARY_DIR}
)
ENDIF(UNIX)


 


