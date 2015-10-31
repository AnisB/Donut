
# SFML finding

add_executable(realisticRendering ${PROGRAM}/realisticRendering)
TARGET_LINK_LIBRARIES(realisticRendering ${CORELIBS})

add_executable(bezierProgram ${PROGRAM}/bezierProgram.cpp)
TARGET_LINK_LIBRARIES(bezierProgram ${CORELIBS})

if(ROOF)
add_executable(roofGeneration ${PROGRAM}/roofGeneration.cpp)
TARGET_LINK_LIBRARIES(roofGeneration ${CORELIBS})
endif(ROOF)