bento_exe("asset_compiler" "programs" "asset_compiler.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
target_link_libraries("asset_compiler" "donut_engine" "bento_sdk" "${THIRD_PARTY_LIBRARIES}")

bento_exe("flour_loader" "programs" "flour_loader.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
target_link_libraries("flour_loader" "donut_engine" "bento_sdk" "${THIRD_PARTY_LIBRARIES}")

# Copy the binaries
copy_next_to_binary("flour_loader" "${THIRD_PARTY_BINARIES}")