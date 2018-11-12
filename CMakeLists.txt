cmake_minimum_required(VERSION 3.5)
project(dst2root)
set(VERSION 1.0.0)

set(CMAKE_MODULE_PATH
   ${CMAKE_MODULE_PATH}
   ${PROJECT_SOURCE_DIR}/cmake
   ${PROJECT_SOURCE_DIR}/cmake/modules)


option(BUILD_LZ4  "Build lz4 libraries" OFF)
set(LZ4_FOUND FALSE)
find_package(LZ4)
IF(${BUILD_LZ4} OR NOT ${LZ4_FOUND})
  add_subdirectory(${PROJECT_SOURCE_DIR}/src)
ENDIF()

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})


include_directories(src/hipocpp)
add_subdirectory(src/hipocpp)

set(CMAKE_CXX_FLAGS ${ROOT_CXX_FLAGS})
add_executable(dst2root src/dst2root.cpp)
target_link_libraries(dst2root hipocpp ${ROOT_LIBRARIES})
