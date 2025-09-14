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

void Renderer::DrawSPO(SingularPixelObject& spo) {
    const Vector2f& spoPos = spo.GetPosition();
    const Vector2i& spoSize = spo.GetSize();
    const std::vector<Vector4>& pixelData = spo.GetDeformedPixelData();

    for (int y = 0; y < spoSize.y; ++y) {
        for (int x = 0; x < spoSize.x; ++x) {
            const Vector4& pixelColor = pixelData[y * spoSize.x + x];
            if (pixelColor.a > 0) {
                float worldX = spoPos.x + static_cast<float>(x);
                float worldY = spoPos.y + static_cast<float>(y);
                DrawWorldPixel(worldX, worldY, pixelColor);
            }
        }
    }
}

Camera& Renderer::GetCamera() {
    return m_Camera;
}
