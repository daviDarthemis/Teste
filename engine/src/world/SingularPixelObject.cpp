#include "world/SingularPixelObject.h"
#include "renderer/Renderer.h" // Precisamos incluir para a definição completa de Vector4

SingularPixelObject::SingularPixelObject(int width, int height)
    : m_Position({0.0f, 0.0f}), m_Size({width, height}) {
    
    // Redimensiona o nosso vetor 1D para conter todos os pixels.
    // O segundo argumento é o valor padrão para cada elemento.
    // Criamos uma cor preta transparente como padrão.
    m_PixelData.resize(width * height, {0, 0, 0, 0});
}

void SingularPixelObject::SetPixel(int x, int y, const Vector4& color) {
    // Verificação de limites para evitar escrever fora da memória do vetor.
    if (x >= 0 && x < m_Size.x && y >= 0 && y < m_Size.y) {
        m_PixelData[y * m_Size.x + x] = color;
    }
}

const Vector4& SingularPixelObject::GetPixel(int x, int y) const {
    // Verificação de limites. Se fora dos limites, retorna uma referência estática
    // para um pixel seguro para evitar crashes.
    if (x >= 0 && x < m_Size.x && y >= 0 && y < m_Size.y) {
        return m_PixelData[y * m_Size.x + x];
    }
    
    static const Vector4 outOfBoundsColor = {255, 0, 255, 255}; // Cor magenta para erros
    return outOfBoundsColor;
}

void SingularPixelObject::SetPosition(const Vector2f& position) {
    m_Position = position;
}

const Vector2f& SingularPixelObject::GetPosition() const {
    return m_Position;
}

const Vector2i& SingularPixelObject::GetSize() const {
    return m_Size;
}
