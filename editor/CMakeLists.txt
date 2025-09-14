# Adiciona um executável para a nossa ferramenta geradora
add_executable(UPM_Generator
    src/upm_generator.cpp
)

# Adiciona os diretórios de inclusão necessários
target_include_directories(UPM_Generator PUBLIC
    ../engine/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Adiciona a definição de pré-processador (-DFNL_IMPL) para gerar a implementação
target_compile_definitions(UPM_Generator PRIVATE FNL_IMPL)
