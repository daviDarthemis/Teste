#include "core/Application.h"
#include "renderer/Renderer.h"
#include "assets/AssetManager.h"
#include "world/SingularPixelObject.h"
#include "simulation/Animator.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

Application::Application()
    : m_Window(nullptr), m_IsRunning(false) {
    m_Renderer = std::make_unique<Renderer>();
}

Application::~Application() = default;

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

    if (!m_Renderer->Init(m_Window)) {
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
        return;
    }

    AssetManager assetManager;
    std::shared_ptr<SingularPixelObject> venomAsset = assetManager.LoadSPO("venom.upm");

    if (!venomAsset) {
        std::cerr << "Falha ao carregar o asset principal. Certifique-se de que 'venom.upm' existe." << std::endl;
        m_Renderer->Shutdown();
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
        return;
    }

    venomAsset->SetPosition({-8.0f, -8.0f});

    Animator animator;

    m_IsRunning = true;
    
    uint32_t startTime = SDL_GetTicks();

    // --- LOOP PRINCIPAL ---
    while (m_IsRunning) {
        // --- CÁLCULO DO TEMPO ---
        float totalTime = (SDL_GetTicks() - startTime) / 1000.0f;

        // --- PROCESSAMENTO DE EVENTOS ---
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_IsRunning = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP: m_Renderer->GetCamera().Move({0.0f, -10.0f / m_Renderer->GetCamera().GetZoom()}); break;
                    case SDLK_DOWN: m_Renderer->GetCamera().Move({0.0f, 10.0f / m_Renderer->GetCamera().GetZoom()}); break;
                    case SDLK_LEFT: m_Renderer->GetCamera().Move({-10.0f / m_Renderer->GetCamera().GetZoom(), 0.0f}); break;
                    case SDLK_RIGHT: m_Renderer->GetCamera().Move({10.0f / m_Renderer->GetCamera().GetZoom(), 0.0f}); break;
                    case SDLK_KP_PLUS: case SDLK_PLUS: m_Renderer->GetCamera().AdjustZoom(0.1f); break;
                    case SDLK_KP_MINUS: case SDLK_MINUS: m_Renderer->GetCamera().AdjustZoom(-0.1f); break;
                }
            }
        }

        // --- LÓGICA DE SIMULAÇÃO / ANIMAÇÃO ---
        animator.ApplyWobble(*venomAsset, totalTime);

        // --- RENDERIZAÇÃO ---
        m_Renderer->BeginFrame();
        m_Renderer->DrawSPO(*venomAsset);
        m_Renderer->EndFrame();
    }

    // --- LIMPEZA ---
    m_Renderer->Shutdown();
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}
