add_library(texture texture.cpp)
target_include_directories(texture PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(texture PUBLIC glfw glad glm shader)