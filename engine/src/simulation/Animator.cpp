#include "simulation/Animator.h"
#include "world/SingularPixelObject.h"
#include <cmath>
#include <algorithm>
#include <string> // Necessário para std::string

void Animator::ApplyWobble(SingularPixelObject& spo, float totalTime) {
    const Vector2i& size = spo.GetSize();
    const std::vector<Vector4>& basePixels = spo.GetBasePixelData();
    std::vector<Vector4>& deformedPixels = spo.GetDeformedPixelData();

    std::fill(deformedPixels.begin(), deformedPixels.end(), Vector4{0, 0, 0, 0});

    float scale = 1.0f + 0.1f * std::sin(totalTime * 3.0f);
    float centerX = size.x / 2.0f;
    float centerY = size.y / 2.0f;

    for (int y = 0; y < size.y; ++y) {
        for (int x = 0; x < size.x; ++x) {
            const Vector4& baseColor = basePixels[y * size.x + x];
            if (baseColor.a > 0) {
                float relativeX = static_cast<float>(x) - centerX;
                float relativeY = static_cast<float>(y) - centerY;
                float newRelativeX = relativeX * scale;
                float newRelativeY = relativeY * scale;
                int deformedX = static_cast<int>(newRelativeX + centerX);
                int deformedY = static_cast<int>(newRelativeY + centerY);
                
                if (deformedX >= 0 && deformedX < size.x && deformedY >= 0 && deformedY < size.y) {
                    deformedPixels[deformedY * size.x + deformedX] = baseColor;
                }
            }
        }
    }
}

// NOVA IMPLEMENTAÇÃO
void Animator::ApplyShear(SingularPixelObject& spo, const std::string& partName, float totalTime) {
    const Vector2i& size = spo.GetSize();
    const std::vector<Vector4>& basePixels = spo.GetBasePixelData();
    std::vector<Vector4>& deformedPixels = spo.GetDeformedPixelData();

    // 1. Encontrar a parte do corpo alvo
    BodyPart* targetPart = nullptr;
    for (auto& part : spo.GetBodyParts()) {
        if (part.name == partName) {
            targetPart = &part;
            break;
        }
    }

    // Se a parte não for encontrada, não faz nada.
    if (!targetPart) {
        return;
    }

    // 2. Copiar a imagem base para a imagem deformada.
    // Desta forma, os píxeis que não pertencem à parte alvo já estarão no lugar correto.
    deformedPixels = basePixels;

    // 3. Calcular o fator de deformação
    // Uma onda senoidal que causa um deslocamento horizontal de até 2 píxeis.
    float shearFactor = 2.0f * std::sin(totalTime * 5.0f); // * 5.0f para uma oscilação mais rápida

    // 4. Iterar APENAS sobre os píxeis da parte alvo
    for (const auto& coord : targetPart->pixelCoordinates) {
        int baseX = coord.x;
        int baseY = coord.y;
        
        const Vector4& baseColor = basePixels[baseY * size.x + baseX];

        // Calcula a nova posição X
        // O cisalhamento é proporcional à altura do pixel na imagem (normalizada)
        float normalizedY = static_cast<float>(baseY) / static_cast<float>(size.y);
        int deformedX = baseX + static_cast<int>(shearFactor * normalizedY);
        int deformedY = baseY; // A altura Y não muda

        // 5. Apagar o pixel da sua posição original no buffer deformado
        deformedPixels[baseY * size.x + baseX] = {0, 0, 0, 0}; // Torna-o transparente

        // 6. Desenhar o pixel na sua nova posição deformada
        if (deformedX >= 0 && deformedX < size.x && deformedY >= 0 && deformedY < size.y) {
            deformedPixels[deformedY * size.x + deformedX] = baseColor;
        }
    }
}
