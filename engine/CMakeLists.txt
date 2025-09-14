# Encontra a biblioteca SDL2 no sistema. Se não encontrar, o CMake dará um erro.
find_package(SDL2 REQUIRED)

# Define a biblioteca da engine.
# UPM_Engine é o nome que daremos à biblioteca.
# STATIC significa que o código da engine será copiado para dentro do executável final do jogo.
add_library(UPM_Engine STATIC
    src/core/Application.cpp
    include/core/Application.h
    src/renderer/Renderer.cpp
    include/renderer/Renderer.h
    src/renderer/Camera.cpp
    include/renderer/Camera.h
    src/world/WorldGrid.cpp
    include/world/WorldGrid.h
    src/world/SingularPixelObject.cpp
    include/world/SingularPixelObject.h
    src/assets/AssetManager.cpp
    include/assets/AssetManager.h
    src/assets/UPM_Parser.cpp
    include/assets/UPM_Parser.h
    src/simulation/Physics.cpp
    include/simulation/Physics.h
)

# Especifica os diretórios de "include" para a nossa engine.
# PUBLIC significa que qualquer projeto que se ligue (link) à UPM_Engine
# também terá acesso a estes diretórios e bibliotecas.
target_include_directories(UPM_Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
)

# Liga a nossa engine contra a biblioteca SDL2.
target_link_libraries(UPM_Engine PUBLIC
    ${SDL2_LIBRARIES}
)
