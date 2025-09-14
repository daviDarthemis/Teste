#include "renderer/Renderer.h"
#include "world/SingularPixelObject.h"
#include <SDL2/SDL.h>
#include <iostream>

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
    Vector2i screenPos = m_Camera.WorldToScreen({worldX, worldY}, m_ScreenWidth, m_ScreenHeight);
    SDL_SetRenderDrawColor(m_SdlRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(m_SdlRenderer, screenPos.x, screenPos.y);
}

void Renderer::DrawSPO(const SingularPixelObject& spo) {
    const Vector2f& spoPos = spo.GetPosition();
    const Vector2i& spoSize = spo.GetSize();

    // Itera por cada pixel local do objeto
    for (int y = 0; y < spoSize.y; ++y) {
        for (int x = 0; x < spoSize.x; ++x) {
            const Vector4& pixelColor = spo.GetPixel(x, y);

            // Otimização: só desenha se não for transparente
            if (pixelColor.a > 0) {
                // Calcula a posição do pixel no mundo
                float worldX = spoPos.x + static_cast<float>(x);
                float worldY = spoPos.y + static_cast<float>(y);

                // Usa a nossa função já existente para desenhar o pixel no mundo
                DrawWorldPixel(worldX, worldY, pixelColor);
            }
        }
    }
}

Camera& Renderer::GetCamera() {
    return m_Camera;
}
