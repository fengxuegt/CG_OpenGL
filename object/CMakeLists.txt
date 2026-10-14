add_library(object object.cpp
        mesh.cpp
        scene.cpp)
target_include_directories(object PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(object PUBLIC glfw glad shader glm)