# Adiciona um executável para a nossa ferramenta geradora
add_executable(UPM_Generator
    src/upm_generator.cpp
)

# Precisamos de dizer ao gerador onde encontrar o ficheiro UPM_Format.h
target_include_directories(UPM_Generator PUBLIC
    ../engine/include
)
