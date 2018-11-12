cmake_minimum_required(VERSION 3.5)

include(ExternalProject)
ExternalProject_Add(LZ4
    GIT_REPOSITORY    https://github.com/lz4/lz4.git
    SOURCE_DIR        ${CMAKE_CURRENT_BINARY_DIR}/lz4
    GIT_TAG    "v1.8.3"
    PATCH_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/lz4_cmake.txt <SOURCE_DIR>/CMakeLists.txt
    INSTALL_COMMAND ""
)
