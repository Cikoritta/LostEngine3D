cmake_minimum_required(VERSION 3.8)

project(LostEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)


add_subdirectory(libs/glfw)

add_subdirectory(libs/glm)

set(GLI_BUILD_TESTS OFF CACHE INTERNAL "Disable gli tests")
set(GLI_BUILD_DUMMY OFF CACHE INTERNAL "Disable gli dummy")
add_subdirectory(libs/gli)


file(GLOB_RECURSE CPP_FILES "LostEngine/*.cpp")
file(GLOB_RECURSE HPP_FILES "LostEngine/*.hpp")

add_executable(LostEngine ${CPP_FILES} ${HPP_FILES})


target_include_directories(LostEngine PRIVATE
    libs/glad/include
    libs/entt/single_include
    LostEngine
)


target_link_libraries(LostEngine
    glad
    glfw
    glm
    gli
)
