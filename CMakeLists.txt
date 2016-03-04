cmake_minimum_required(VERSION 2.8)
project(lua-poly2tri)
enable_language(CXX)

include_directories (${PROJECT_SOURCE_DIR}/poly2tri/poly2tri)
add_subdirectory(poly2tri)

find_package(LUA 5.1 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

set(SOURCE_FILES
  src/lua-poly2tri.cpp)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(lua-poly2tri SHARED ${SOURCE_FILES})

set_target_properties(lua-poly2tri PROPERTIES PREFIX "")
set_target_properties(lua-poly2tri PROPERTIES OUTPUT_NAME "poly2tri")

if (APPLE)
  set(PLATFORM_OPTIONS "-undefined dynamic_lookup")
  set_target_properties(lua-poly2tri PROPERTIES SUFFIX .so)
elseif(UNIX)
  set(PLATFORM_OPTIONS "-fpic")
elseif(WIN32)
  set(PLATFORM_OPTIONS ${LUA_LIBRARIES})
endif (APPLE)

target_link_libraries(lua-poly2tri ${PLATFORM_OPTIONS} poly2tri)
