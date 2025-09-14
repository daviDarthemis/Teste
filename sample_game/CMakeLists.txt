# Define o executável do nosso jogo.
# "Game" será o nome do ficheiro final.
add_executable(Game
    src/main.cpp
)

# Liga o nosso executável "Game" à biblioteca "UPM_Engine".
# O CMake sabe o que é "UPM_Engine" porque foi definida no diretório da engine.
# Esta linha é a conexão crucial entre o jogo e a engine.
target_link_libraries(Game PRIVATE UPM_Engine)
