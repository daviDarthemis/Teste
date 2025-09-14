#include "world/SingularPixelObject.h"

SingularPixelObject::SingularPixelObject(int width, int height)
    : m_Position({0.0f, 0.0f}), m_Size({width, height}) {
    
    // Inicializa ambos os buffers com píxeis transparentes.
    m_BasePixelData.resize(width * height, {0, 0, 0, 0});
    m_DeformedPixelData.resize(width * height, {0, 0, 0, 0});
}

// Métodos para o buffer de BASE
void SingularPixelObject::SetBasePixel(int x, int y, const Vector4& color) {
    if (x >= 0 && x < m_Size.x && y >= 0 && y < m_Size.y) {
        int index = y * m_Size.x + x;
        m_BasePixelData[index] = color;
        m_DeformedPixelData[index] = color; // Inicializa o buffer deformado com o mesmo valor.
    }
}

const Vector4& SingularPixelObject::GetBasePixel(int x, int y) const {
    if (x >= 0 && x < m_Size.x && y >= 0 && y < m_Size.y) {
        return m_BasePixelData[y * m_Size.x + x];
    }
    static const Vector4 outOfBoundsColor = {255, 0, 255, 255};
    return outOfBoundsColor;
}

const std::vector<Vector4>& SingularPixelObject::GetBasePixelData() const {
    return m_BasePixelData;
}

// Métodos para o buffer DEFORMADO
std::vector<Vector4>& SingularPixelObject::GetDeformedPixelData() {
    return m_DeformedPixelData;
}

// Métodos de Posição e Tamanho
void SingularPixelObject::SetPosition(const Vector2f& position) {
    m_Position = position;
}

const Vector2f& SingularPixelObject::GetPosition() const {
    return m_Position;
}

const Vector2i& SingularPixelObject::GetSize() const {
    return m_Size;
}
