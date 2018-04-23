bento_exe("wavefrontConverter" "programs" "wavefrontConverter.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
target_link_libraries("wavefrontConverter" "donut_engine" "bento_sdk")

bento_exe("asset_compiler" "programs" "asset_compiler.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
target_link_libraries("asset_compiler" "donut_engine" "bento_sdk")