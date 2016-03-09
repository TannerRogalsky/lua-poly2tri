cmake_minimum_required(VERSION 2.8)
project(lua-poly2tri)
enable_language(CXX)

set(lua-poly2tri_VERSION_MAJOR 1)
set(lua-poly2tri_VERSION_MINOR 0)
set(lua-poly2tri_AUTHOR "Tanner Rogalsky <tanner@tannerrogalsky.com>")

configure_file (
  "${PROJECT_SOURCE_DIR}/src/lua-poly2tri.h.in"
  "${PROJECT_BINARY_DIR}/lua-poly2tri.h"
)

include_directories (${PROJECT_SOURCE_DIR}/poly2tri/poly2tri)
add_subdirectory(poly2tri)

include_directories (${PROJECT_SOURCE_DIR}/lua-5.1.5/etc ${PROJECT_SOURCE_DIR}/lua-5.1.5/src)
add_subdirectory(lua-5.1.5)

set(SOURCE_FILES src/lua-poly2tri.cpp)
include_directories(${CMAKE_SOURCE_DIR}/src ${PROJECT_BINARY_DIR})

add_library(lua-poly2tri SHARED ${SOURCE_FILES})

set_target_properties(lua-poly2tri PROPERTIES PREFIX "")
set_target_properties(lua-poly2tri PROPERTIES OUTPUT_NAME "poly2tri")

if (APPLE)
  set(PLATFORM_OPTIONS "-undefined dynamic_lookup")
  set_target_properties(lua-poly2tri PROPERTIES SUFFIX .so)
elseif(WIN32)
  set(PLATFORM_OPTIONS lua51)
endif (APPLE)

target_link_libraries(lua-poly2tri ${PLATFORM_OPTIONS} poly2tri)
