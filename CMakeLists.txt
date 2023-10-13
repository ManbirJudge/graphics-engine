# password of gupt bhandar 4564

# ------
cmake_minimum_required(VERSION 3.0)
project(GraphicsEngine)

# adding source files
add_executable(GraphicsEngine 
    main.cpp

    Camera.cpp
    EBO.cpp
    Log.cpp
    Mesh.cpp
    Shader.cpp
    Texture.cpp
    VAO.cpp
    VBO.cpp

    stb.cpp
    glad.c
)


# configuring include directories
target_include_directories(GraphicsEngine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/include
)

# configuring OpenGL
find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})

# configuring GLFW
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)

set(ENKITS_BUILD_EXAMPLES OFF CACHE BOOL "Build basic example applications")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL  "GLFW lib only")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)

# linking libraries to the project
target_link_libraries(GraphicsEngine ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES})
