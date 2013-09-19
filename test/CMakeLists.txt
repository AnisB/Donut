
add_definitions( -DDONUT_TESTS)
#  SFML finding
add_executable(testStateEngine ${TEST}/testStateEngine.cpp)
TARGET_LINK_LIBRARIES(testStateEngine Donut ${CORELIBS})


add_executable(testRenderer ${TEST}/testRenderer.cpp)
TARGET_LINK_LIBRARIES(testRenderer Donut ${CORELIBS})


add_executable(testMovingShapes ${TEST}/testMovingShapes.cpp ${TEST}/EngineExample1.cpp )
TARGET_LINK_LIBRARIES(testMovingShapes Donut ${CORELIBS})


add_executable(testFrameCanvas ${TEST}/testFrameCanvas.cpp ${TEST}/EngineExample2.cpp )
TARGET_LINK_LIBRARIES(testFrameCanvas Donut ${CORELIBS})


add_executable(testRenderToTexture ${TEST}/testRenderToTexture.cpp ${TEST}/EngineExample3.cpp )
TARGET_LINK_LIBRARIES(testRenderToTexture Donut ${CORELIBS})

 


