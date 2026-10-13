add_library(light light.cpp directionallight.cpp ambientlight.cpp pointlight.cpp)
target_include_directories(light PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(light PUBLIC glfw glad shader glm texture object)