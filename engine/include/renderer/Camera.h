#pragma once
#include "core/Types.h" // Incluímos os nossos novos tipos de vetores

class Camera {
public:
    Camera();

    // Funções de controlo da câmara
    void SetPosition(const Vector2f& position);
    void Move(const Vector2f& offset);
    void SetZoom(float zoomLevel);
    void AdjustZoom(float amount);

    // Funções de acesso
    const Vector2f& GetPosition() const;
    float GetZoom() const;

    // A matemática principal: conversão de coordenadas
    Vector2i WorldToScreen(const Vector2f& worldPosition, int screenWidth, int screenHeight) const;
    Vector2f ScreenToWorld(const Vector2i& screenPosition, int screenWidth, int screenHeight) const;

private:
    Vector2f m_Position;
    float m_Zoom;
};
