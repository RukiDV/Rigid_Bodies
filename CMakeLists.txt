cmake_minimum_required(VERSION 3.19)
project(Rigid_Bodies)
set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES src/main.cpp src/window.cpp src/primitives.cpp src/movement.cpp src/shader.cpp)

add_executable(Rigid_Bodies ${SOURCE_FILES})
find_package(SDL2 REQUIRED)
find_package(OpenGL)
find_package(glm)
find_package(GLEW REQUIRED)

target_include_directories(Rigid_Bodies PRIVATE "${PROJECT_SOURCE_DIR}/include" ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_link_libraries(Rigid_Bodies SDL2::SDL2main SDL2::SDL2 OpenGL::OpenGL GLEW::GLEW)
