add_library(light material.cpp phongmaterial.cpp
        ../light/directionallight.cpp
        ../light/include/directionallight.h
        ../light/include/ambientlight.cpp
        ../light/include/ambientlight.h)
target_include_directories(light PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(light PUBLIC glfw glad shader glm texture)