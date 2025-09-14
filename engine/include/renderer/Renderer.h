#pragma once

#include "core/Types.h"
#include "renderer/Camera.h"

// Forward declarations
struct Vector4;
struct SDL_Window;
struct SDL_Renderer;
class SingularPixelObject; // Forward declare a nossa nova classe

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Init(SDL_Window* window);
    void Shutdown();
    void BeginFrame();
    void EndFrame();

    void DrawWorldPixel(float worldX, float worldY, const Vector4& color);
    
    // A nova função para desenhar um objeto inteiro.
    void DrawSPO(const SingularPixelObject& spo);

    Camera& GetCamera();

private:
    SDL_Renderer* m_SdlRenderer;
    Camera m_Camera;

    int m_ScreenWidth;
    int m_ScreenHeight;
};
