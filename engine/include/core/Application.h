#pragma once

#include <memory>

// Forward declarations para todas as classes que são membros ou usadas como ponteiros.
struct SDL_Window;
class Renderer; // Usamos uma forward declaration aqui.

class Application {
public:
    Application();
    ~Application();

    void Run();

private:
    SDL_Window* m_Window;
    
    // Isto é um problema. Um membro por valor requer a definição completa da classe.
    // Vamos alterá-lo para um ponteiro para desacoplar totalmente.
    // Esta é uma mudança de design importante, mas que resolve muitos problemas de dependência.
    std::unique_ptr<Renderer> m_Renderer;

    bool m_IsRunning;
};
