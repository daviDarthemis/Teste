#include "assets/UPM_Format.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <cstring> // Para strncpy

struct Color { uint8_t r, g, b, a; };

int main() {
    std::cout << "Gerador de UPM v1.0 (com Dados de Corpo)" << std::endl;

    // --- Definição dos Dados ---
    UPM_Format::Header header;
    header.magic = 0x204D5055;
    header.version = 1;

    UPM_Format::Manifest manifest;
    manifest.imageWidth = 16;
    manifest.imageHeight = 16;

    std::vector<Color> imageData;
    imageData.resize(manifest.imageWidth * manifest.imageHeight);

    Color black = {20, 20, 20, 255};
    Color white = {255, 255, 255, 255};
    
    // NOVO: Estrutura para os dados do corpo a serem gerados
    UPM_Format::BodyPartHeader corePartHeader;
    std::vector<UPM_Format::PixelCoord> corePartPixels;

    // Preenche a imagem e define as partes do corpo ao mesmo tempo
    for (uint16_t y = 0; y < manifest.imageHeight; ++y) {
        for (uint16_t x = 0; x < manifest.imageWidth; ++x) {
            bool isBorder = (x == 0 || x == manifest.imageWidth - 1 || y == 0 || y == manifest.imageHeight - 1);
            imageData[y * manifest.imageWidth + x] = isBorder ? white : black;
            
            // Se não for uma borda, pertence à parte "core"
            if (!isBorder) {
                corePartPixels.push_back({x, y});
            }
        }
    }

    // Preenche os metadados da parte do corpo
    strncpy(corePartHeader.name, "core", 32);
    corePartHeader.pixelCount = corePartPixels.size();

    // --- Calcular Offsets ---
    header.manifestOffset = sizeof(UPM_Format::Header);
    header.imageDataOffset = header.manifestOffset + sizeof(UPM_Format::Manifest);
    header.bodyDataOffset = header.imageDataOffset + (imageData.size() * sizeof(Color));

    // --- Escrever o Ficheiro Binário ---
    std::ofstream outFile("venom.upm", std::ios::binary);
    if (!outFile) {
        std::cerr << "Erro ao criar o ficheiro venom.upm" << std::endl;
        return 1;
    }

    outFile.write(reinterpret_cast<const char*>(&header), sizeof(header));
    outFile.write(reinterpret_cast<const char*>(&manifest), sizeof(manifest));
    outFile.write(reinterpret_cast<const char*>(imageData.data()), imageData.size() * sizeof(Color));

    // Escreve os dados do corpo
    uint32_t partCount = 1; // Temos apenas uma parte por agora
    outFile.write(reinterpret_cast<const char*>(&partCount), sizeof(partCount));
    outFile.write(reinterpret_cast<const char*>(&corePartHeader), sizeof(corePartHeader));
    outFile.write(reinterpret_cast<const char*>(corePartPixels.data()), corePartPixels.size() * sizeof(UPM_Format::PixelCoord));

    outFile.close();

    std::cout << "Ficheiro 'venom.upm' com dados de corpo gerado com sucesso." << std::endl;
    return 0;
}
