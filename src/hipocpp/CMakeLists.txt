cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS ${ROOT_CXX_FLAGS})
add_definitions(-fPIC)
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
ELSE()
  target_link_libraries(hipocpp PRIVATE lz4)
ENDIF()
