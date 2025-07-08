cmake_minimum_required(VERSION 3.8)

project(LostEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(LIB_PATH "${CMAKE_SOURCE_DIR}/libs")


add_library(glad STATIC ${LIB_PATH}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${LIB_PATH}/glad/include)


add_subdirectory(${LIB_PATH}/glfw)


add_subdirectory(${LIB_PATH}/glm/glm)


file(GLOB_RECURSE CPP_FILES "src/*.cpp")

add_executable(LostEngine ${CPP_FILES})


set(RESOURCE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(RESOURCE_TARGET_DIR "${CMAKE_BINARY_DIR}")

add_custom_command(TARGET LostEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCE_SOURCE_DIR}"
        "${RESOURCE_TARGET_DIR}"
)


target_include_directories(LostEngine PRIVATE
    ${LIB_PATH}/glad/include
    ${LIB_PATH}/entt/single_include
    ${LIB_PATH}/glm
    ${LIB_PATH}/simpleini
    ${LIB_PATH}/stb-master
    LostEngine
)


target_link_libraries(LostEngine
    glad
    glfw
    glm
)
