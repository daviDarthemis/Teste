#pragma once

#include "core/Types.h"
#include "renderer/Camera.h"

// Forward declarations
struct SDL_Window;
struct SDL_Renderer;
class SingularPixelObject;

class Renderer {
public:
    Renderer();
    ~Renderer(); // O destrutor agora é importante por causa do unique_ptr na Application

    bool Init(SDL_Window* window);
    void Shutdown();
    void BeginFrame();
    void EndFrame();

    void DrawWorldPixel(float worldX, float worldY, const Vector4& color);
    void DrawSPO(const SingularPixelObject& spo);

    Camera& GetCamera();

private:
    SDL_Renderer* m_SdlRenderer;
    Camera m_Camera;
    int m_ScreenWidth;
    int m_ScreenHeight;
};
