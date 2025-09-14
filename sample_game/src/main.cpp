#include "core/Application.h"

int main(int argc, char* argv[]) {
    // 1. Cria uma instância da nossa engine.
    Application app;
    
    // 2. Executa a engine.
    // Esta chamada bloqueia e só retorna quando o loop do jogo terminar (a janela for fechada).
    app.Run();

    // 3. Termina o programa.
    return 0;
}
