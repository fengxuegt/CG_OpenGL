add_library(shader shader.cpp)
target_include_directories(shader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(shader PUBLIC glfw glad glm)