#include "renderer/Camera.h"
#include <algorithm> // Usado para std::max

// Construtor: define um estado inicial padrão para a câmara.
Camera::Camera() : m_Position({0.0f, 0.0f}), m_Zoom(1.0f) {
}

void Camera::SetPosition(const Vector2f& position) {
    m_Position = position;
}

void Camera::Move(const Vector2f& offset) {
    m_Position.x += offset.x;
    m_Position.y += offset.y;
}

void Camera::SetZoom(float zoomLevel) {
    // Evita zoom zero ou negativo que quebraria a matemática.
    m_Zoom = std::max(0.1f, zoomLevel);
}

void Camera::AdjustZoom(float amount) {
    SetZoom(m_Zoom + amount);
}

const Vector2f& Camera::GetPosition() const {
    return m_Position;
}

float Camera::GetZoom() const {
    return m_Zoom;
}

Vector2i Camera::WorldToScreen(const Vector2f& worldPosition, int screenWidth, int screenHeight) const {
    // 1. Transladar o ponto do mundo em relação à posição da câmara
    Vector2f relativePos = {worldPosition.x - m_Position.x, worldPosition.y - m_Position.y};

    // 2. Aplicar o zoom
    relativePos.x *= m_Zoom;
    relativePos.y *= m_Zoom;

    // 3. Transladar do centro da visão (0,0) para o centro da tela (largura/2, altura/2)
    Vector2i screenPosition = {
        static_cast<int>(relativePos.x + screenWidth / 2.0f),
        static_cast<int>(relativePos.y + screenHeight / 2.0f)
    };

    return screenPosition;
}

Vector2f Camera::ScreenToWorld(const Vector2i& screenPosition, int screenWidth, int screenHeight) const {
    // Este é o processo inverso exato de WorldToScreen

    // 1. Transladar do centro da tela para o centro da visão
    Vector2f relativePos = {
        static_cast<float>(screenPosition.x) - screenWidth / 2.0f,
        static_cast<float>(screenPosition.y) - screenHeight / 2.0f
    };

    // 2. Desfazer o zoom
    relativePos.x /= m_Zoom;
    relativePos.y /= m_Zoom;

    // 3. Desfazer a translação da câmara para obter a posição final no mundo
    Vector2f worldPosition = {
        relativePos.x + m_Position.x,
        relativePos.y + m_Position.y
    };

    return worldPosition;
}
