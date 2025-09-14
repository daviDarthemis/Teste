#include "renderer/Renderer.h"
#include <SDL2/SDL.h>
#include <iostream>

// A definição do Vector4 move-se para cá, já que apenas o Renderer a usa.
struct Vector4 {
    unsigned char r, g, b, a;
};

Renderer::Renderer() : m_SdlRenderer(nullptr), m_ScreenWidth(0), m_ScreenHeight(0) {
}

Renderer::~Renderer() {
}

bool Renderer::Init(SDL_Window* window) {
    if (m_SdlRenderer) {
        SDL_DestroyRenderer(m_SdlRenderer);
    }
    m_SdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_SdlRenderer) {
        std::cerr << "Erro ao criar o renderizador SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    // Obtém e armazena o tamanho da janela.
    SDL_GetWindowSize(window, &m_ScreenWidth, &m_ScreenHeight);

    return true;
}

void Renderer::Shutdown() {
    if (m_SdlRenderer) {
        SDL_DestroyRenderer(m_SdlRenderer);
        m_SdlRenderer = nullptr;
    }
}

void Renderer::BeginFrame() {
    SDL_SetRenderDrawColor(m_SdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_SdlRenderer);
}

void Renderer::EndFrame() {
    SDL_RenderPresent(m_SdlRenderer);
}

void Renderer::DrawWorldPixel(float worldX, float worldY, const Vector4& color) {
    // 1. Converte a coordenada do mundo para a coordenada da tela usando a câmara.
    Vector2i screenPos = m_Camera.WorldToScreen({worldX, worldY}, m_ScreenWidth, m_ScreenHeight);

    // 2. Define a cor e desenha o ponto na coordenada da tela.
    SDL_SetRenderDrawColor(m_SdlRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(m_SdlRenderer, screenPos.x, screenPos.y);
}

Camera& Renderer::GetCamera() {
    return m_Camera;
}
