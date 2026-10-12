add_library(material material.cpp phongmaterial.cpp)
target_include_directories(material PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(material PUBLIC glfw glad shader glm texture)