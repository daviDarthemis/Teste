#pragma once

#include "core/Types.h" // Inclui a definição completa de Vector2f, Vector2i, e Vector4
#include <vector>

class SingularPixelObject {
public:
    // Construtor: cria um objeto com uma dimensão específica, preenchido com uma cor padrão (transparente).
    SingularPixelObject(int width, int height);
    
    // Define a cor de um pixel específico dentro do objeto.
    void SetPixel(int x, int y, const Vector4& color);

    // Obtém a cor de um pixel específico (const para garantir que não modificamos o objeto).
    const Vector4& GetPixel(int x, int y) const;

    // Define a posição do objeto no mundo.
    void SetPosition(const Vector2f& position);

    // Obtém a posição do objeto no mundo.
    const Vector2f& GetPosition() const;

    // Obtém as dimensões do objeto (largura e altura).
    const Vector2i& GetSize() const;

private:
    Vector2f m_Position;
    Vector2i m_Size;
    
    // Usamos um vetor 1D para armazenar os dados dos pixels.
    // Isto é mais eficiente em termos de memória (um único bloco contíguo)
    // do que um vetor de vetores. O acesso é feito com a fórmula: index = y * largura + x.
    std::vector<Vector4> m_PixelData;
};
