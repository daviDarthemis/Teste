#include "simulation/Animator.h"
#include "world/SingularPixelObject.h"
#include <cmath>
#include <algorithm>
#include <string>

// ... (As implementações de ApplyWobble e ApplyShear permanecem exatamente as mesmas)
void Animator::ApplyWobble(SingularPixelObject& spo, const std::string& partName, float totalTime) {
    const Vector2i& size = spo.GetSize();
    const std::vector<Vector4>& basePixels = spo.GetBasePixelData();
    std::vector<Vector4>& deformedPixels = spo.GetDeformedPixelData();
    BodyPart* targetPart = nullptr;
    for (auto& part : spo.GetBodyParts()) {
        if (part.name == partName) {
            targetPart = &part;
            break;
        }
    }
    if (!targetPart) { return; }
    float scale = 1.0f + 0.1f * std::sin(totalTime * 3.0f);
    float centerX = size.x / 2.0f;
    float centerY = size.y / 2.0f;
    for (const auto& coord : targetPart->pixelCoordinates) {
        int baseX = coord.x;
        int baseY = coord.y;
        const Vector4& baseColor = basePixels[baseY * size.x + baseX];
        deformedPixels[baseY * size.x + baseX] = {0, 0, 0, 0};
        float relativeX = static_cast<float>(baseX) - centerX;
        float relativeY = static_cast<float>(baseY) - centerY;
        int deformedX = static_cast<int>((relativeX * scale) + centerX);
        int deformedY = static_cast<int>((relativeY * scale) + centerY);
        if (deformedX >= 0 && deformedX < size.x && deformedY >= 0 && deformedY < size.y) {
            deformedPixels[deformedY * size.x + deformedX] = baseColor;
        }
    }
}

void Animator::ApplyShear(SingularPixelObject& spo, const std::string& partName, float totalTime) {
    const Vector2i& size = spo.GetSize();
    const std::vector<Vector4>& basePixels = spo.GetBasePixelData();
    std::vector<Vector4>& deformedPixels = spo.GetDeformedPixelData();
    BodyPart* targetPart = nullptr;
    for (auto& part : spo.GetBodyParts()) {
        if (part.name == partName) {
            targetPart = &part;
            break;
        }
    }
    if (!targetPart) { return; }
    float shearFactor = 2.0f * std::sin(totalTime * 5.0f);
    for (const auto& coord : targetPart->pixelCoordinates) {
        int baseX = coord.x;
        int baseY = coord.y;
        const Vector4& baseColor = basePixels[baseY * size.x + baseX];
        float normalizedY = static_cast<float>(baseY) / static_cast<float>(size.y);
        int deformedX = baseX + static_cast<int>(shearFactor * normalizedY);
        int deformedY = baseY;
        deformedPixels[baseY * size.x + baseX] = {0, 0, 0, 0};
        if (deformedX >= 0 && deformedX < size.x && deformedY >= 0 && deformedY < size.y) {
            deformedPixels[deformedY * size.x + deformedX] = baseColor;
        }
    }
}


// NOVA IMPLEMENTAÇÃO
void Animator::ApplyGooeyFilter(SingularPixelObject& spo) {
    const Vector2i& size = spo.GetSize();
    std::vector<Vector4>& pixels = spo.GetDeformedPixelData();

    // Criamos uma cópia para ler, pois não podemos modificar e ler o mesmo vetor ao mesmo tempo.
    const auto pixelsReadCopy = pixels;

    // Itera por todos os píxeis interiores (ignora a borda de 1 pixel)
    for (int y = 1; y < size.y - 1; ++y) {
        for (int x = 1; x < size.x - 1; ++x) {
            int currentIndex = y * size.x + x;

            // Se o pixel atual estiver vazio (transparente)
            if (pixelsReadCopy[currentIndex].a == 0) {
                // Verificar vizinhos na horizontal e vertical
                const auto& left  = pixelsReadCopy[currentIndex - 1];
                const auto& right = pixelsReadCopy[currentIndex + 1];
                const auto& up    = pixelsReadCopy[currentIndex - size.x];
                const auto& down  = pixelsReadCopy[currentIndex + size.x];

                // Regra 1: Preencher lacunas horizontais
                if (left.a > 0 && right.a > 0) {
                    // Preenche com a média das cores dos vizinhos
                    unsigned char avgR = (left.r + right.r) / 2;
                    unsigned char avgG = (left.g + right.g) / 2;
                    unsigned char avgB = (left.b + right.b) / 2;
                    pixels[currentIndex] = {avgR, avgG, avgB, 255};
                }
                // Regra 2: Preencher lacunas verticais
                else if (up.a > 0 && down.a > 0) {
                    unsigned char avgR = (up.r + down.r) / 2;
                    unsigned char avgG = (up.g + down.g) / 2;
                    unsigned char avgB = (up.b + down.b) / 2;
                    pixels[currentIndex] = {avgR, avgG, avgB, 255};
                }
            }
        }
    }
}
