#include "simulation/Animator.h"
#include "world/SingularPixelObject.h"
#include <cmath> // Para std::sin e std::cos
#include <algorithm> // para std::fill

void Animator::ApplyWobble(SingularPixelObject& spo, float totalTime) {
    const Vector2i& size = spo.GetSize();
    const std::vector<Vector4>& basePixels = spo.GetBasePixelData();
    std::vector<Vector4>& deformedPixels = spo.GetDeformedPixelData();

    // Limpa o buffer deformado com píxeis transparentes antes de o redesenhar
    std::fill(deformedPixels.begin(), deformedPixels.end(), Vector4{0, 0, 0, 0});

    // Calcula um fator de escala que oscila suavemente entre ~0.9 e ~1.1
    float scale = 1.0f + 0.1f * std::sin(totalTime * 3.0f); // O * 3.0f controla a velocidade da pulsação

    // O centro do objeto, a partir do qual a escala será aplicada
    float centerX = size.x / 2.0f;
    float centerY = size.y / 2.0f;

    // Itera por cada pixel da imagem BASE
    for (int y = 0; y < size.y; ++y) {
        for (int x = 0; x < size.x; ++x) {
            const Vector4& baseColor = basePixels[y * size.x + x];

            // Se o pixel base não for transparente
            if (baseColor.a > 0) {
                // 1. Calcula a posição do pixel relativa ao centro
                float relativeX = static_cast<float>(x) - centerX;
                float relativeY = static_cast<float>(y) - centerY;

                // 2. Aplica a escala a essa posição
                float newRelativeX = relativeX * scale;
                float newRelativeY = relativeY * scale;

                // 3. Converte de volta para coordenadas de píxeis no objeto
                int deformedX = static_cast<int>(newRelativeX + centerX);
                int deformedY = static_cast<int>(newRelativeY + centerY);
                
                // 4. Escreve a cor do pixel base na sua NOVA posição no buffer DEFORMADO
                // (Com verificação de limites para não escrever fora do vetor)
                if (deformedX >= 0 && deformedX < size.x && deformedY >= 0 && deformedY < size.y) {
                    deformedPixels[deformedY * size.x + deformedX] = baseColor;
                }
            }
        }
    }
}
