#pragma once

#include "core/Types.h"
#include "world/Body.h" // Incluir a nossa nova definição
#include <vector>

class SingularPixelObject {
public:
    SingularPixelObject(int width, int height);
    
    // Métodos de Píxeis (Base e Deformado)
    void SetBasePixel(int x, int y, const Vector4& color);
    const Vector4& GetBasePixel(int x, int y) const;
    const std::vector<Vector4>& GetBasePixelData() const;
    std::vector<Vector4>& GetDeformedPixelData();

    // Métodos de Posição e Tamanho
    void SetPosition(const Vector2f& position);
    const Vector2f& GetPosition() const;
    const Vector2i& GetSize() const;

    // NOVO: Métodos para o Corpo
    std::vector<BodyPart>& GetBodyParts();
    const std::vector<BodyPart>& GetBodyParts() const;

private:
    Vector2f m_Position;
    Vector2i m_Size;
    
    std::vector<Vector4> m_BasePixelData;
    std::vector<Vector4> m_DeformedPixelData;

    std::vector<BodyPart> m_BodyParts; // NOVO: O contentor para o esqueleto
};
