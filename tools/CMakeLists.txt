add_library(tools tools.cpp
        assimploader.cpp)
target_include_directories(tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tools  shader object material texture assimp::assimp)