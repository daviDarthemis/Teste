#include "renderer/Renderer.h"
#include <SDL2/SDL.h>
#include <iostream>

Renderer::Renderer() : m_SdlRenderer(nullptr) {
    // Construtor inicializa o ponteiro a null.
}

Renderer::~Renderer() {
    // O destrutor está vazio. A limpeza é feita explicitamente em Shutdown()
    // para garantir a ordem correta de destruição (primeiro o renderer, depois a janela).
}

bool Renderer::Init(SDL_Window* window) {
    // Se já tivermos um renderizador, destruímo-lo primeiro.
    if (m_SdlRenderer) {
        SDL_DestroyRenderer(m_SdlRenderer);
    }

    // Cria o renderizador SDL.
    m_SdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (!m_SdlRenderer) {
        std::cerr << "Erro ao criar o renderizador SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Renderer::Shutdown() {
    if (m_SdlRenderer) {
        SDL_DestroyRenderer(m_SdlRenderer);
        m_SdlRenderer = nullptr;
    }
}

void Renderer::BeginFrame() {
    // Define a cor de limpeza para preto.
    SDL_SetRenderDrawColor(m_SdlRenderer, 0, 0, 0, 255);
    // Limpa o ecrã com essa cor.
    SDL_RenderClear(m_SdlRenderer);
}

void Renderer::EndFrame() {
    // Apresenta o buffer de volta para a janela.
    SDL_RenderPresent(m_SdlRenderer);
}

void Renderer::DrawPixel(int x, int y, const Vector4& color) {
    // Define a cor de desenho para a cor do pixel.
    SDL_SetRenderDrawColor(m_SdlRenderer, color.r, color.g, color.b, color.a);
    // Desenha um ponto (pixel) na coordenada especificada.
    SDL_RenderDrawPoint(m_SdlRenderer, x, y);
}
