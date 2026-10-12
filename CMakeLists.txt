cmake_minimum_required(VERSION 3.30)
project(CG_OpenGL)

set(CMAKE_CXX_STANDARD 20)

#glfw
find_package(glfw3 3.3 REQUIRED)
#glad
add_subdirectory(thirdparty/glad)
#shader
add_subdirectory(shader)
#geometry
add_subdirectory(geometry)
#glm
add_subdirectory(thirdparty/glm)
#texture
add_subdirectory(texture)
#camera
add_subdirectory(camera)
#object
add_subdirectory(object)
#material
add_subdirectory(material)
#复制文件
# 复制文件
file(GLOB ASSETS "./assets" )
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})




add_executable(CG_OpenGL_createwindow createwindow.cpp)
add_executable(CG_OpenGL_framebuffer framebuffer_record.cpp)

target_link_libraries(CG_OpenGL_createwindow glad glfw shader geometry glm texture camera object material)
target_link_libraries(CG_OpenGL_framebuffer glad glfw shader geometry glm camera)




