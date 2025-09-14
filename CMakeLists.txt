# Versão mínima do CMake exigida
cmake_minimum_required(VERSION 3.16)

# Nome do projeto global
project(UnixPixelMechanics VERSION 1.0)

# Define o padrão do C++ a ser usado em todo o projeto (C++17 é um bom padrão moderno)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Informa ao CMake para procurar e processar os CMakeLists.txt nos subdiretórios
add_subdirectory(engine)
add_subdirectory(sample_game)
add_subdirectory(editor) # <<<--- ESTA É A LINHA QUE FALTAVA
