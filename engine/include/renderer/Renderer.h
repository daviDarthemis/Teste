#pragma once

#include "core/Types.h"
#include "renderer/Camera.h" // Incluir a nossa nova câmara

struct Vector4; // A definição está em Renderer.cpp, forward declare é suficiente
struct SDL_Window;
struct SDL_Renderer;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Init(SDL_Window* window);
    void Shutdown();
    void BeginFrame();
    void EndFrame();

    // A nossa função de desenho agora opera em coordenadas do MUNDO (float).
    void DrawWorldPixel(float worldX, float worldY, const Vector4& color);
    
    // Fornece acesso à câmara para que a Application possa controlá-la.
    Camera& GetCamera();

private:
    SDL_Renderer* m_SdlRenderer;
    Camera m_Camera; // O Renderer agora tem uma Câmara.

    // Guarda as dimensões da tela para uso da câmara.
    int m_ScreenWidth;
    int m_ScreenHeight;
};
