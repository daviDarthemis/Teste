#include "core/Application.h"
#include <SDL2/SDL.h>
#include <iostream>

// Incluímos os nossos tipos porque o Vector4 foi movido para o .cpp do Renderer.
#include "renderer/Renderer.h" 
struct Vector4 { unsigned char r, g, b, a; };

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

    m_IsRunning = true;

    // --- LOOP PRINCIPAL ---
    while (m_IsRunning) {
        // --- PROCESSAMENTO DE EVENTOS ---
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_IsRunning = false;
            }
            // Verifica se uma tecla foi pressionada
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    // Controlo de movimento da câmara
                    case SDLK_UP:
                        m_Renderer.GetCamera().Move({0.0f, -10.0f / m_Renderer.GetCamera().GetZoom()});
                        break;
                    case SDLK_DOWN:
                        m_Renderer.GetCamera().Move({0.0f, 10.0f / m_Renderer.GetCamera().GetZoom()});
                        break;
                    case SDLK_LEFT:
                        m_Renderer.GetCamera().Move({-10.0f / m_Renderer.GetCamera().GetZoom(), 0.0f});
                        break;
                    case SDLK_RIGHT:
                        m_Renderer.GetCamera().Move({10.0f / m_Renderer.GetCamera().GetZoom(), 0.0f});
                        break;
                    // Controlo de zoom da câmara
                    case SDLK_q:
                        m_Renderer.GetCamera().AdjustZoom(0.1f);
                        break;
                    case SDLK_e:
                        m_Renderer.GetCamera().AdjustZoom(-0.1f);
                        break;
                }
            }
        }

        // --- RENDERIZAÇÃO ---
        m_Renderer.BeginFrame();

        // ** TESTE: Desenha uma cruz branca na ORIGEM DO MUNDO (0, 0) **
        Vector4 whiteColor = {255, 255, 255, 255};
        for(int i = -10; i <= 10; ++i) {
            m_Renderer.DrawWorldPixel(static_cast<float>(i), 0.0f, whiteColor); // Linha Horizontal
            m_Renderer.DrawWorldPixel(0.0f, static_cast<float>(i), whiteColor); // Linha Vertical
        }
        
        m_Renderer.EndFrame();
    }

    // --- LIMPEZA ---
    m_Renderer.Shutdown();
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}
