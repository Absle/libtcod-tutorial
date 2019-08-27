add_library(
    libtuto STATIC
    src/Cmp_Position.cpp
    src/Entity.cpp
    src/IComponent.cpp
    src/Input.cpp
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