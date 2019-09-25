add_library(
    libtuto STATIC
    src/ecs/Component_Common.cpp
    src/ecs/Component_Manager.cpp
    src/ecs/Entity_Manager.cpp
    src/ecs/System.cpp
    src/Input.cpp
)

target_include_directories(
    libtuto
    INTERFACE include
    INTERFACE include/ecs
    PRIVATE include
    PRIVATE include/ecs
)

target_link_libraries(
    libtuto
    libtcod
)