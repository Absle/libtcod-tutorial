add_library(
    libtuto STATIC
    src/Component_Common.cpp
    src/Entity_Manager.cpp
    src/Input.cpp
    src/System.cpp
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