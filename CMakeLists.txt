cmake_minimum_required(VERSION 3.0.2)

project(DonutEngine)

IF(SILENT)
add_definitions( -D _SILENT )
ENDIF(SILENT)

set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG")

# Setting the compiler data
set(CMAKE_BUILD_TYPE "Debug")
IF (NOT WIN32)
add_definitions(-std=c++11) 
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
ENDIF()
SET(CMAKE_MACRO_DIRS "${PROJECT_SOURCE_DIR}/cmake/")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")
link_directories(${CMAKE_BINARY_DIR} /usr/local/lib/)

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

include(${CMAKE_MACRO_DIRS}/Macros.cmake)

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
  INCLUDE_DIRECTORIES ( /System/Library/Frameworks /usr/local/include/)
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
set(CMAKE_CXX_FLAGS_DEBUG "/MDd")
FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
SET(GRAPHIC_LIBS "${EXTERNAL_LIBS}/lib-vc2015/glfw3.lib" "${EXTERNAL_LIBS}/glew32.lib" "${EXTERNAL_LIBS}/glew32s.lib" "opengl32.lib" "${EXTERNAL_LIBS}/libjpeg.lib")
SET(CORELIBS ${GRAPHIC_LIBS} )
ENDIF()

# Generating the libraries
GENERATE_LIB("${SOURCES}/base" Base)
GENERATE_LIB("${SOURCES}/butter" Butter)
GENERATE_LIB("${SOURCES}/engine" Engine)
GENERATE_LIB("${SOURCES}/input" Input)
GENERATE_LIB("${SOURCES}/multithread" MultiThread)
GENERATE_LIB("${SOURCES}/render" Render)
GENERATE_LIB("${SOURCES}/core" Core)
GENERATE_LIB("${SOURCES}/graphics" Graphics)
GENERATE_LIB("${SOURCES}/resource" Resource)
GENERATE_LIB("${SOURCES}/stateengine" StateEngine)
GENERATE_LIB("${SOURCES}/tools" Tools)
GENERATE_LIB("${SOURCES}/tracing" Tracing)

SET(CORELIBS ${CORELIBS} Base Butter Engine Input Core MultiThread Render Graphics Resource StateEngine Tools Tracing)

# Adding the tests if we should
IF(NO_TESTS)
ELSE(NO_TESTS)
add_subdirectory(${TEST})
ENDIF(NO_TESTS)

# Adding the programs if we should
add_subdirectory(${PROGRAM})


# Adding the links on linux and mac
IF(UNIX)
add_custom_command(
    TARGET Tracing POST_BUILD
    COMMAND ln -sf ${PROJECT_SOURCE_DIR}/assets ${PROJECT_BINARY_DIR}
)
ENDIF(UNIX)


IF(WIN32)
#sources
file(TO_NATIVE_PATH "${PROJECT_SOURCE_DIR}/assets" link2)
#global target
file(TO_NATIVE_PATH "${PROJECT_BINARY_DIR}/program/assets" programData)

file(TO_NATIVE_PATH "${PROJECT_BINARY_DIR}/test/assets" testData)
execute_process( COMMAND cmd.exe /c mklink /D ${programData} ${link2})
execute_process( COMMAND cmd.exe /c mklink /D ${programShaders} ${link1})
execute_process( COMMAND cmd.exe /c mklink /D ${testData} ${link2})
execute_process( COMMAND cmd.exe /c mklink /D ${testShaders} ${link1})
ENDIF(WIN32)


 


