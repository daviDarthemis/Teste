find_package(SDL2 REQUIRED)

add_library(UPM_Engine STATIC
    src/core/Application.cpp
    include/core/Application.h
    include/core/Types.h

    src/renderer/Renderer.cpp
    include/renderer/Renderer.h
    src/renderer/Camera.cpp
    include/renderer/Camera.h

    src/world/World.cpp
    include/world/World.h
    src/world/SingularPixelObject.cpp
    include/world/SingularPixelObject.h
    include/world/Body.h
    include/world/Component.h
    src/world/ComponentFactory.cpp
    include/world/ComponentFactory.h

    src/assets/AssetManager.cpp
    include/assets/AssetManager.h
    src/assets/UPM_Parser.cpp
    include/assets/UPM_Parser.h

    src/simulation/Physics.cpp
    include/simulation/Physics.h
    src/simulation/Animator.cpp
    include/simulation/Animator.h
    src/simulation/ShearAnimationComponent.cpp
    include/simulation/ShearAnimationComponent.h
    src/simulation/WobbleAnimationComponent.cpp
    include/simulation/WobbleAnimationComponent.h
    src/simulation/WaveAnimationComponent.cpp # Adicionado
    include/simulation/WaveAnimationComponent.h # Adicionado
)

target_include_directories(UPM_Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(UPM_Engine PUBLIC
    ${SDL2_LIBRARIES}
)

