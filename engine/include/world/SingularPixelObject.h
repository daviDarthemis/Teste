#pragma once

#include "core/Types.h"
#include <vector>

class SingularPixelObject {
public:
    SingularPixelObject(int width, int height);
    
    // Métodos para manipular os dados de BASE (a forma original)
    void SetBasePixel(int x, int y, const Vector4& color);
    const Vector4& GetBasePixel(int x, int y) const;
    const std::vector<Vector4>& GetBasePixelData() const; // Para o Animator ler

    // Métodos para manipular os dados DEFORMADOS (a forma atual)
    std::vector<Vector4>& GetDeformedPixelData(); // Para o Animator escrever

    void SetPosition(const Vector2f& position);
    const Vector2f& GetPosition() const;
    const Vector2i& GetSize() const;

private:
    Vector2f m_Position;
    Vector2i m_Size;
    
    std::vector<Vector4> m_BasePixelData;     // A forma original, nunca muda após o carregamento.
    std::vector<Vector4> m_DeformedPixelData; // A forma a ser desenhada, modificada a cada frame.
};
