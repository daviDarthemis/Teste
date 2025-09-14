#include "assets/UPM_Format.h"
#include "vendor/FastNoiseLite.h" // A inclusão está correta
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <cstring>
#include <ctime>

struct Color { uint8_t r, g, b, a; };

int main() {
    std::cout << "Gerador de UPM v2.0 (com Geração de Forma por Ruído)" << std::endl;

    // --- Configuração da Geração Procedural (usando a API C) ---
    // 1. Criar o estado do ruído
    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
    // Usar uma semente aleatória para que cada geração seja diferente
    srand(time(NULL));
    noise.seed = rand(); 
    noise.frequency = 0.1f; // Frequência mais baixa = características maiores/mais suaves

    float noiseThreshold = 0.0f; // Píxeis com ruído > 0.0 serão sólidos

    // --- Definição dos Dados ---
    UPM_Format::Header header;
    header.magic = 0x204D5055;
    header.version = 1;

    UPM_Format::Manifest manifest;
    manifest.imageWidth = 16;
    manifest.imageHeight = 16;
    
    std::vector<Color> imageData(manifest.imageWidth * manifest.imageHeight);
    Color black = {20, 20, 20, 255};
    Color white = {255, 255, 255, 255};
    Color transparent = {0, 0, 0, 0};

    UPM_Format::BodyPartHeader corePartHeader;
    std::vector<UPM_Format::PixelCoord> corePartPixels;

    // --- Geração da Imagem e do Corpo ---
    for (uint16_t y = 0; y < manifest.imageHeight; ++y) {
        for (uint16_t x = 0; x < manifest.imageWidth; ++x) {
            // 2. Obter o valor do ruído usando a função C
            float noiseValue = fnlGetNoise2D(&noise, (float)x, (float)y);
            
            // Se o ruído estiver acima do limiar, o píxel é sólido
            if (noiseValue > noiseThreshold) {
                // Adicionar uma borda branca simples à forma
                float borderNoise = fnlGetNoise3D(&noise, (float)x, (float)y, 42.0f); // Usar um 3º eixo para uma semente diferente
                if (borderNoise > 0.5f) {
                    imageData[y * manifest.imageWidth + x] = white;
                } else {
                    imageData[y * manifest.imageWidth + x] = black;
                }
                corePartPixels.push_back({x, y});
            } else {
                imageData[y * manifest.imageWidth + x] = transparent;
            }
        }
    }

    strncpy(corePartHeader.name, "core", 32);
    corePartHeader.pixelCount = corePartPixels.size();

    // --- Definir Componentes ---
    std::vector<UPM_Format::ComponentDescriptor> components;
    UPM_Format::ComponentDescriptor wobbleDesc;
    wobbleDesc.type = 2;
    strncpy(wobbleDesc.targetPart, "core", 32);
    components.push_back(wobbleDesc);

    // --- Calcular Offsets e Escrever Ficheiro ---
    size_t imageDataSize = imageData.size() * sizeof(Color);
    size_t corePartDataSize = sizeof(corePartHeader) + (corePartPixels.size() * sizeof(UPM_Format::PixelCoord));
    size_t bodyDataSize = sizeof(uint32_t) + corePartDataSize;
    size_t componentDataSize = sizeof(uint32_t) + (components.size() * sizeof(UPM_Format::ComponentDescriptor));

    header.manifestOffset = sizeof(UPM_Format::Header);
    header.imageDataOffset = header.manifestOffset + sizeof(UPM_Format::Manifest);
    header.bodyDataOffset = header.imageDataOffset + imageDataSize;
    header.componentDataOffset = header.bodyDataOffset + bodyDataSize;

    std::ofstream outFile("venom.upm", std::ios::binary);
    if (!outFile) { return 1; }

    outFile.write(reinterpret_cast<const char*>(&header), sizeof(header));
    outFile.write(reinterpret_cast<const char*>(&manifest), sizeof(manifest));
    outFile.write(reinterpret_cast<const char*>(imageData.data()), imageDataSize);

    uint32_t partCount = 1;
    outFile.write(reinterpret_cast<const char*>(&partCount), sizeof(partCount));
    outFile.write(reinterpret_cast<const char*>(&corePartHeader), sizeof(corePartHeader));
    outFile.write(reinterpret_cast<const char*>(corePartPixels.data()), corePartPixels.size() * sizeof(UPM_Format::PixelCoord));

    uint32_t componentCount = components.size();
    outFile.write(reinterpret_cast<const char*>(&componentCount), sizeof(componentCount));
    outFile.write(reinterpret_cast<const char*>(components.data()), componentDataSize);

    outFile.close();
    std::cout << "Ficheiro 'venom.upm' com forma de blob gerada processualmente com sucesso." << std::endl;
    return 0;
}
