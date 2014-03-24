
add_definitions( -DDONUT_TESTS)
# SFML finding
add_executable(testStateEngine ${TEST}/testStateEngine.cpp)
TARGET_LINK_LIBRARIES(testStateEngine Donut ${CORELIBS})

add_executable(testRenderer ${TEST}/testRenderer.cpp)
TARGET_LINK_LIBRARIES(testRenderer Donut ${CORELIBS})

add_executable(testInput ${TEST}/testInput.cpp)
TARGET_LINK_LIBRARIES(testInput Donut ${CORELIBS})

add_executable(testModelLoader ${TEST}/testModelLoader.cpp)
TARGET_LINK_LIBRARIES(testModelLoader Donut ${CORELIBS})

add_executable(testDisplay ${TEST}/testDisplay.cpp)
TARGET_LINK_LIBRARIES(testDisplay Donut ${CORELIBS})

add_executable(testMapPNT ${TEST}/testMapPNT.cpp)
TARGET_LINK_LIBRARIES(testMapPNT Donut ${CORELIBS})

add_executable(testOutline ${TEST}/testOutline.cpp)
TARGET_LINK_LIBRARIES(testOutline Donut ${CORELIBS})

add_executable(testObjLoad ${TEST}/testObjLoad.cpp)
TARGET_LINK_LIBRARIES(testObjLoad Donut ${CORELIBS})

add_executable(testMultiThreadRender ${TEST}/testMultiThreadRender.cpp ${TEST}/engineexample1.cpp)
TARGET_LINK_LIBRARIES(testMultiThreadRender Donut ${CORELIBS})

add_executable(testDefferedLight ${TEST}/testDefferedLight.cpp)
TARGET_LINK_LIBRARIES(testDefferedLight Donut ${CORELIBS})

add_executable(testSkybox ${TEST}/testSkybox.cpp)
TARGET_LINK_LIBRARIES(testSkybox Donut ${CORELIBS})

add_executable(testTesselation ${TEST}/testTesselation.cpp)
TARGET_LINK_LIBRARIES(testTesselation Donut ${CORELIBS})

add_executable(bezierProgram ${TEST}/bezierProgram.cpp)
TARGET_LINK_LIBRARIES(bezierProgram Donut ${CORELIBS})

add_executable(testModelToTexture ${TEST}/testModelToTexture.cpp)
TARGET_LINK_LIBRARIES(testModelToTexture Donut ${CORELIBS})

add_executable(testRayTracer ${TEST}/testRayTracer.cpp)
TARGET_LINK_LIBRARIES(testRayTracer Donut ${CORELIBS})