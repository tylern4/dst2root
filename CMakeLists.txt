cmake_minimum_required(VERSION 3.5)
project(dst2root)
set(VERSION 1.0.0)

set(CMAKE_MODULE_PATH
   ${CMAKE_MODULE_PATH}
   ${PROJECT_SOURCE_DIR}/cmake
   ${PROJECT_SOURCE_DIR}/cmake/modules)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})

include_directories(hipocpp)
add_subdirectory(hipocpp)

set(CMAKE_CXX_FLAGS ${ROOT_CXX_FLAGS})
add_executable(dst2root dst2root.cpp)
target_link_libraries(dst2root hipocpp ${ROOT_LIBRARIES})
