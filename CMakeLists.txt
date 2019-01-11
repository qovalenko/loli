cmake_minimum_required(VERSION 3.0.2)
project("Loli" C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ldl -s -O2 -Wall")

set(LOLI_MAJOR "0")
set(LOLI_MINOR "6")
add_definitions(-DLOLI_VERSION="${LOLI_MAJOR}.${LOLI_MINOR}")

file(GLOB_RECURSE LOLI_SRC src/*.c src/*.h)
list(FILTER LOLI_SRC EXCLUDE REGEX ".*loli.c$")

file(GLOB_RECURSE REMOVE_CMAKE "cmake-build-debug/*")
list(REMOVE_ITEM LOLI_SRC ${REMOVE_CMAKE})

add_library(libloli_obj OBJECT ${LOLI_SRC})
add_library(libloli SHARED $<TARGET_OBJECTS:libloli_obj>)

if(NOT MINGW AND NOT WIN32 AND NOT MSVC)
  set_target_properties(libloli_obj PROPERTIES COMPILE_FLAGS "-fPIC")
endif()

set_target_properties(libloli PROPERTIES PREFIX "")

add_executable(loli src/loli.c $<TARGET_OBJECTS:libloli_obj>)
target_link_libraries(loli m)
target_link_libraries(libloli m)
