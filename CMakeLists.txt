cmake_minimum_required(VERSION 3.20)

set(WARNINGS_AS_ERRORS_FOR_GET_SYSTEM_ERROR OFF CACHE BOOL "ON iff you want to treat warnings as errors")

add_library(get_system_error)
add_library(Cool::get_system_error ALIAS get_system_error)
target_compile_features(get_system_error PUBLIC cxx_std_11)

# ---Add source files---
if(WARNINGS_AS_ERRORS_FOR_GET_SYSTEM_ERROR)
    target_include_directories(get_system_error PUBLIC include)
else()
    target_include_directories(get_system_error SYSTEM PUBLIC include)
endif()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
target_sources(get_system_error PRIVATE ${SRC_FILES})

# ---Set warning level---
if(MSVC)
    target_compile_options(get_system_error PRIVATE /W4)
else()
    target_compile_options(get_system_error PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion -Wimplicit-fallthrough)
endif()

# ---Maybe enable warnings as errors---
if(WARNINGS_AS_ERRORS_FOR_GET_SYSTEM_ERROR)
    if(MSVC)
        target_compile_options(get_system_error PRIVATE /WX)
    else()
        target_compile_options(get_system_error PRIVATE -Werror)
    endif()
endif()
