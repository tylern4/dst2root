cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS ${ROOT_CXX_FLAGS})
set(LZ4_FOUND FALSE)
find_package(LZ4)
IF(NOT ${LZ4_FOUND})
  message(FATAL_ERROR "Build with makefile instead to build lz4" )
ENDIF()

add_definitions(-D__LZ4__)
add_library(hipocpp STATIC
      data.cpp
      dictionary.cpp
      event.cpp
      node.cpp
      reader.cpp
      record.cpp
      text.cpp
      utils.cpp
      wrapper.cpp
      writer.cpp
)


IF(${LZ4_FOUND})
  target_link_libraries(hipocpp PRIVATE ${LZ4_LIBRARY})
ENDIF()
