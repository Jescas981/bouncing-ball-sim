cmake_minimum_required(VERSION 3.25.1)
project(BouncingBall)

find_package(OpenGL REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendor)

add_executable(main "src/main.c" "src/generator.c" "src/shader.c" 
                    "src/io.c" "src/program.c" "src/physics.c" 
                    "src/gmath.c" 
                    "src/gameobject.c" "src/components/physics.c"
                    "src/components/renderer.c" "src/components/collider.c"
                    "src/components/transform.c" "src/systems/physics.c"
                    "src/systems/collider.c" "src/systems/renderer.c")
target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(main PRIVATE c_std_99)
target_compile_options(main PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(main PRIVATE OpenGL::OpenGL glfw glad)