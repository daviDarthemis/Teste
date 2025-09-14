#include "core/Application.h"
#include "renderer/Renderer.h"
#include "assets/AssetManager.h"
#include "world/World.h"
#include "world/SingularPixelObject.h"
#include "world/ComponentFactory.h"
#include "world/Component.h"
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
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { /* ... */ return; }
    m_Window = SDL_CreateWindow("Unix Pixel Mechanics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!m_Window) { /* ... */ SDL_Quit(); return; }
    if (!m_Renderer->Init(m_Window)) { /* ... */ SDL_DestroyWindow(m_Window); SDL_Quit(); return; }

    World world;
    AssetManager assetManager;
    Animator animator;

    std::shared_ptr<SingularPixelObject> venomEntity = assetManager.LoadSPO("venom.upm");
    if (!venomEntity) { /* ... */ return; }

    for (const auto& request : venomEntity->GetComponentRequests()) {
        auto component = ComponentFactory::Create(request, animator);
        if (component) {
            venomEntity->AddComponent(std::move(component));
        }
    }

    venomEntity->SetPosition({-8.0f, -8.0f});
    world.AddEntity(venomEntity);

    m_IsRunning = true;
    uint32_t lastFrameTime = SDL_GetTicks();

    while (m_IsRunning) {
        uint32_t currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentTime;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { m_IsRunning = false; }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP: m_Renderer->GetCamera().Move({0.0f, -10.0f / m_Renderer->GetCamera().GetZoom()}); break;
                    case SDLK_DOWN: m_Renderer->GetCamera().Move({0.0f, 10.0f / m_Renderer->GetCamera().GetZoom()}); break;
                    case SDLK_LEFT: m_Renderer->GetCamera().Move({-10.0f / m_Renderer->GetCamera().GetZoom(), 0.0f}); break;
                    case SDLK_RIGHT: m_Renderer->GetCamera().Move({10.0f / m_Renderer->GetCamera().GetZoom(), 0.0f}); break;
                    case SDLK_KP_PLUS: case SDLK_l: m_Renderer->GetCamera().AdjustZoom(0.1f); break;
                    case SDLK_KP_MINUS: case SDLK_r: m_Renderer->GetCamera().AdjustZoom(-0.1f); break;
                }
            }
        }
        
        // --- ATUALIZAÇÃO ---
        // Agora passamos o animator para o mundo.
        world.Update(deltaTime, animator);

        // --- RENDERIZAÇÃO ---
        m_Renderer->BeginFrame();
        for (const auto& entity : world.GetEntities()) {
            m_Renderer->DrawSPO(*entity);
        }
        m_Renderer->EndFrame();
    }

    m_Renderer->Shutdown();
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}
