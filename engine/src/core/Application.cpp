#include "core/Application.h"
#include <SDL2/SDL.h>
#include <iostream>

Application::Application() 
    : m_Window(nullptr), m_IsRunning(false) {
    // O construtor do m_Renderer já é chamado automaticamente.
}

Application::~Application() {
    // O destrutor também já é chamado automaticamente.
}

void Application::Run() {
    // --- INICIALIZAÇÃO ---
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        return;
    }

    m_Window = SDL_CreateWindow(
        "Unix Pixel Mechanics",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    if (!m_Window) {
        std::cerr << "Erro ao criar a janela: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Inicializa o nosso próprio Renderer, passando a janela que criámos.
    if (!m_Renderer.Init(m_Window)) {
        // Se a inicialização do renderer falhar, limpamos e saímos.
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
        return;
    }

    m_IsRunning = true;

    // --- LOOP PRINCIPAL ---
    while (m_IsRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_IsRunning = false;
            }
        }

        // --- RENDERIZAÇÃO ABSTRAÍDA ---
        // A Application já não sabe sobre SDL_RenderClear, etc.
        m_Renderer.BeginFrame();

        // ** NOSSO TESTE: Desenhar um pixel branco no centro da tela **
        // A tela tem 800x600, o centro é 400, 300.
        Vector4 whiteColor = {255, 255, 255, 255};
        m_Renderer.DrawPixel(400, 300, whiteColor);
        
        // ** NOSSO TESTE 2: Desenhar uma cruz vermelha **
        Vector4 redColor = {255, 0, 0, 255};
        for(int i = -5; i <= 5; ++i) {
            m_Renderer.DrawPixel(200 + i, 200, redColor); // Linha horizontal
            m_Renderer.DrawPixel(200, 200 + i, redColor); // Linha vertical
        }

        m_Renderer.EndFrame();
    }

    // --- LIMPEZA ---
    // A ordem é importante: primeiro desliga o renderer, depois destrói a janela.
    m_Renderer.Shutdown();
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}
