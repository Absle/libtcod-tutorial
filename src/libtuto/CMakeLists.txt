add_library(
    libtuto STATIC
    src/input_manager.cpp
)

target_include_directories(
    libtuto 
    INTERFACE include
    PRIVATE include
)

target_link_libraries(
    libtuto
    libtcod
)