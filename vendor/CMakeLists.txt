include(FetchContent)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_X11 ON)


FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        latest
)

# FetchContent_Declare(
#     cglm
#     GIT_REPOSITORY https://github.com/recp/cglm
#     GIT_TAG        v0.9.4
# )

FetchContent_MakeAvailable(glfw)
# FetchContent_MakeAvailable(cglm)

add_subdirectory(glad)