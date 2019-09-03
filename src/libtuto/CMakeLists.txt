add_library(
    libtuto STATIC
    src/Cmp_Move.cpp
    src/Cmp_Position.cpp
    src/Cmp_Sprite.cpp
    src/Entity_Manager.cpp
    src/Entity.cpp
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