add_library(
    libsatk STATIC
    src/ecs/Component_Manager.cpp
    src/ecs/Entity_Manager.cpp
    src/Input.cpp
    src/System.cpp
)

target_include_directories(
    libsatk
    INTERFACE include
    INTERFACE include/ecs
    INTERFACE include/components
    PRIVATE include
    PRIVATE include/ecs
    PRIVATE include/components
)

target_link_libraries(
    libsatk
    libtcod
)