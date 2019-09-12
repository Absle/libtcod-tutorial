cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CXX_STANDARD 17) # TODO update to latest version of cmake so we can do this properly

project(
    libtcod-tut
    VERSION 0.1.0.0
    LANGUAGES CXX
)

# should help install into correct locations on all platforms, eventually
include(GNUInstallDirs)

# adding standard library to dirs for .clang_complete generation
set(dirs "${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}/c++/${CMAKE_CXX_COMPILER_VERSION}")

# adding cmake modules folder to relevant path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
#message(STATUS "module_path=${CMAKE_MODULE_PATH}")

# adding libtcod package
find_package(libtcod REQUIRED)
add_library(libtcod SHARED IMPORTED)
set_property(TARGET libtcod PROPERTY IMPORTED_LOCATION ${libtcod_LIBRARIES})
#target_include_directories(libtcod INTERFACE ${libtcod_INCLUDE_DIRS})
set_property(TARGET libtcod PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${libtcod_INCLUDE_DIRS})
list(APPEND dirs ${libtcod_INCLUDE_DIRS}) #adding to dirs for .clang_complete

# add subdirectories, libs first, app second
add_subdirectory(libtuto)
add_subdirectory(app)

# REMOVED: .clang_complete no longer need after move to VSCode
# generating .clang_complete file 
#message(STATUS "Generating ${CMAKE_SOURCE_DIR}/.clang_complete")
##get_property(dirs DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY INCLUDE_DIRECTORIES)
#message(STATUS "dirs=${dirs}")
#file(WRITE "${CMAKE_SOURCE_DIR}/.clang_complete" "")
#foreach(dir ${dirs})
#    file(APPEND "${CMAKE_SOURCE_DIR}/.clang_complete" "-I${dir}\n")
#endforeach()
#message(STATUS "flags=${CMAKE_CXX_FLAGS}")
#string(REPLACE "'" "" CMAKE_CXX_FLAGS_SPLIT "${CMAKE_CXX_FLAGS}")
#string(REPLACE " " ";" CMAKE_CXX_FLAGS_SPLIT "${CMAKE_CXX_FLAGS_SPLIT}")
#foreach(flag ${CMAKE_C_FLAGS_SPLIT})
#    file(APPEND "${CMAKE_SOURCE_DIR}/.clang_complete" "${flag}\n")
#endforeach()
