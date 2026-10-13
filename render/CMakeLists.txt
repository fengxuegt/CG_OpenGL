add_library(render render.cpp)
target_include_directories(render PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(render PUBLIC glfw glad shader glm texture camera object material light)