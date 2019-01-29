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

set(LZ4_FOUND FALSE)
find_package(LZ4 REQUIRED)

include_directories(src/hipocpp)
add_subdirectory(src/hipocpp)

set(CMAKE_CXX_FLAGS ${ROOT_CXX_FLAGS})
add_executable(dst2root src/dst2root.cpp)
target_link_libraries(dst2root hipocpp ${ROOT_LIBRARIES})

install(TARGETS dst2root
        RUNTIME DESTINATION bin)
