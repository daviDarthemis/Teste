#pragma once

#include "renderer/Renderer.h" // Incluímos o nosso novo módulo

// Forward declaration
struct SDL_Window;

class Application {
public:
    Application();
    ~Application();

    void Run();

private:
    SDL_Window* m_Window;

    // A aplicação agora tem uma instância do nosso Renderer.
    // O ponteiro SDL_Renderer foi removido daqui.
    Renderer m_Renderer; 

    bool m_IsRunning;
};
