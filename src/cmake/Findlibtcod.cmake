#.rst:
# Findlibtcod
# -----------
#
# Finds the libtcod library
#
# This will define the following variables::
#
#   libtcod_FOUND - True if the system has the libtcod library
#   libtcod_INCLUDE_DIRS - The directory the libtcod headers live.
#   libtcod_LIBRARIES - The final set of library directories for libtcod in one variable.
#   libtcod_VERSION - The version of the libtcode library which was found
#
# and the following imported targets::
#
#   libtcod::libtcod - The libtcod library (TODO: REMOVE)
#

set(libtcod_INCLUDE_DIR "/usr/local/include/libtcod/" CACHE FILEPATH "Path to libtcod includes.")
set(libtcod_LIBRARY "/usr/local/lib/libtcod.so" CACHE FILEPATH "Path to libtcod shared library.")
#message(STATUS "DEBUG libcod_cache=${libtcod_LIBRARY}")
set(libtcod_VERSION "1.13.0")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    libtcod
    FOUND_VAR libtcod_FOUND
    REQUIRED_VARS
        libtcod_INCLUDE_DIR
        libtcod_LIBRARY
    VERSION_VAR libtcod_VERSION
)

if(libtcod_FOUND)
    set(libtcod_INCLUDE_DIRS ${libtcod_INCLUDE_DIR})
    set(libtcod_LIBRARIES ${libtcod_LIBRARY})
endif()

mark_as_advanced(
    libtcod_INCLUDE_DIR
    libtcod_LIBRARY
)
