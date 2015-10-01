
# SFML finding

add_executable(realisticRendering ${PROGRAM}/realisticRendering)
TARGET_LINK_LIBRARIES(realisticRendering Donut ${CORELIBS})

add_executable(bezierProgram ${PROGRAM}/bezierProgram.cpp)
TARGET_LINK_LIBRARIES(bezierProgram Donut ${CORELIBS})

add_executable(roofGeneration ${PROGRAM}/roofGeneration.cpp)
TARGET_LINK_LIBRARIES(roofGeneration Donut ${CORELIBS})
