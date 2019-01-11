cmake_minimum_required(VERSION 3.0.2)
project("Loli" C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s -O2 -Wall")

set(LOLI_MAJOR "0")
set(LOLI_MINOR "5")
add_definitions(-DLOLI_VERSION="${LOLI_MAJOR}.${LOLI_MINOR}")

file(GLOB LOLI_SRC *.c *.h)
list(FILTER LOLI_SRC EXCLUDE REGEX ".*loli.c$")

add_library(libloli_obj OBJECT ${LOLI_SRC})
add_library(libloli SHARED $<TARGET_OBJECTS:libloli_obj>)

set_target_properties(libloli_obj PROPERTIES COMPILE_FLAGS "-fPIC")
set_target_properties(libloli PROPERTIES PREFIX "")

add_executable(loli loli.c $<TARGET_OBJECTS:libloli_obj>)
target_link_libraries(loli m)
target_link_libraries(libloli m)
