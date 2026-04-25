cmake_minimum_required(VERSION 3.10)
project(openglmadness)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

set(SOURCES
    src/main.cpp
    src/glad.c
    src/VBO.cpp
    src/EBO.cpp
    src/VAO.cpp
    src/shaderClass.cpp
)

add_executable(MyGame ${SOURCES})

target_include_directories(MyGame PRIVATE headers external/include)

# Link the libraries
target_link_libraries(MyGame 
    PRIVATE 
    OpenGL::GL 
    glfw
)

# Copy the shaders folder to the build directory so the executable can find it
file(COPY "${CMAKE_SOURCE_DIR}/resources/shaders" 
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/resources")