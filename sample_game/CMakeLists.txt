add_executable(Game
    src/main.cpp
)

# Não vamos mais copiar o diretório, pois o ficheiro será gerado pela nossa ferramenta.

target_link_libraries(Game PRIVATE UPM_Engine)
