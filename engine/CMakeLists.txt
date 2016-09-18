cmake_minimum_required(VERSION 3.6)

project(daybreak)

set(CMAKE_MODULE_PATH "${daybreak_SOURCE_DIR}/../cmake")
message("module path" ${CMAKE_MODULE_PATH})

include(CMakeMacros)

set(SOURCE_ROOT ${daybreak_SOURCE_DIR})

message("source root: " ${SOURCE_ROOT})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Profile")

set(CMAKE_C_FLAGS_PROFILE "${CMAKE_C_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_STATIC_LINKER_FLAGS_PROFILE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE}")
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")
set(CMAKE_EXE_LINKER_FLAGS_PROFILE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")


add_compile_options($<$<CONFIG:PROFILE>:-DPROFILE>)
add_compile_options($<$<CONFIG:DEBUG>:/Od> $<$<NOT:$<CONFIG:DEBUG>>:/Ox>)

include_directories(${SOURCE_ROOT})

# platform libraries
add_subdirectory(${SOURCE_ROOT}/platform/win32)

add_subdirectory(${SOURCE_ROOT}/core)


add_subdirectory(${SOURCE_ROOT}/main)

