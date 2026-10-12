add_library(geometry triangle.cpp plane.cpp
        geometry.cpp)
target_include_directories(geometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(geometry PUBLIC glfw glad shader glm)