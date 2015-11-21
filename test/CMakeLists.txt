
add_definitions( -DDONUT_TESTS)
# SFML finding
add_executable(testStateEngine ${TEST}/testStateEngine.cpp)
TARGET_LINK_LIBRARIES(testStateEngine ${CORELIBS})

add_executable(testRenderer ${TEST}/testRenderer.cpp)
TARGET_LINK_LIBRARIES(testRenderer ${CORELIBS})

add_executable(testInput ${TEST}/testInput.cpp)
TARGET_LINK_LIBRARIES(testInput ${CORELIBS})

add_executable(testDisplay ${TEST}/testDisplay.cpp)
TARGET_LINK_LIBRARIES(testDisplay ${CORELIBS})

add_executable(testMapPNT ${TEST}/testMapPNT.cpp)
TARGET_LINK_LIBRARIES(testMapPNT ${CORELIBS})

add_executable(testObjLoad ${TEST}/testObjLoad.cpp)
TARGET_LINK_LIBRARIES(testObjLoad ${CORELIBS})

add_executable(testSkybox ${TEST}/testSkybox.cpp)
TARGET_LINK_LIBRARIES(testSkybox ${CORELIBS})

add_executable(testRayTracer ${TEST}/testRayTracer.cpp)
TARGET_LINK_LIBRARIES(testRayTracer ${CORELIBS})

add_executable(testSceneParse ${TEST}/testSceneParse.cpp)
TARGET_LINK_LIBRARIES(testSceneParse ${CORELIBS})

add_executable(testSceneLoad ${TEST}/testSceneLoad.cpp)
TARGET_LINK_LIBRARIES(testSceneLoad ${CORELIBS})