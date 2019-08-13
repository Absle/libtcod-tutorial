add_library(
    libtuto STATIC
    src/*.cpp
)

target_include_directories(
    libtuto INTERFACE
    include/*.hpp
)

target_link_libraries(
    libtuto
    libtcod
)