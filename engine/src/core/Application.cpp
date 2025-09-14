#include "core/Application.h"
#include <SDL2/SDL.h>
#include <iostream>

#include "renderer/Renderer.h"
#include "world/SingularPixelObject.h"

Application::Application() 
    : m_Window(nullptr), m_IsRunning(false) {
}

Application::~Application() {
}

void Application::Run() {
    // --- INICIALIZAÇÃO ---
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        return;
    }

    m_Window = SDL_CreateWindow("Unix Pixel Mechanics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!m_Window) {
        std::cerr << "Erro ao criar a janela: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    if (!m_Renderer.Init(m_Window)) {
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
        return;
    }

    // --- CRIAÇÃO DO OBJETO DE TESTE ---
    SingularPixelObject venomPrototype(16, 16);
    venomPrototype.SetPosition({-8.0f, -8.0f}); // Centraliza o objeto na origem do mundo

    Vector4 black = {20, 20, 20, 255};
    Vector4 white = {255, 255, 255, 255};
    
    // Preenche o objeto com o nosso desenho de teste
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            // Cria uma borda branca
            if (x == 0 || x == 15 || y == 0 || y == 15) {
                venomPrototype.SetPixel(x, y, white);
            } else {
                venomPrototype.SetPixel(x, y, black);
            }
        }
    }

    m_IsRunning = true;

    // --- LOOP PRINCIPAL ---
    while (m_IsRunning) {
        // --- PROCESSAMENTO DE EVENTOS ---
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_IsRunning = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP: m_Renderer.GetCamera().Move({0.0f, -10.0f / m_Renderer.GetCamera().GetZoom()}); break;
                    case SDLK_DOWN: m_Renderer.GetCamera().Move({0.0f, 10.0f / m_Renderer.GetCamera().GetZoom()}); break;
                    case SDLK_LEFT: m_Renderer.GetCamera().Move({-10.0f / m_Renderer.GetCamera().GetZoom(), 0.0f}); break;
                    case SDLK_RIGHT: m_Renderer.GetCamera().Move({10.0f / m_Renderer.GetCamera().GetZoom(), 0.0f}); break;
                    case SDLK_KP_PLUS: case SDLK_PLUS: m_Renderer.GetCamera().AdjustZoom(0.1f); break;
                    case SDLK_KP_MINUS: case SDLK_MINUS: m_Renderer.GetCamera().AdjustZoom(-0.1f); break;
                }
            }
        }

        // --- RENDERIZAÇÃO ---
        m_Renderer.BeginFrame();
        
        // A nossa chamada de desenho agora é muito mais limpa e de alto nível
        m_Renderer.DrawSPO(venomPrototype);

        m_Renderer.EndFrame();
    }

    // --- LIMPEZA ---
    m_Renderer.Shutdown();
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}
