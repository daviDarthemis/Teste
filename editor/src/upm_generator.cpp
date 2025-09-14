#include "assets/UPM_Format.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

// O nosso Vector4 para trabalhar com cores.
struct Color {
    uint8_t r, g, b, a;
};

int main() {
    std::cout << "Gerador de UPM v1.0" << std::endl;

    UPM_Format::Header header;
    header.magic = 0x204D5055; // 'UPM ' (U=55, P=50, M=4D, ' '=20)
    header.version = 1;

    UPM_Format::Manifest manifest;
    manifest.imageWidth = 16;
    manifest.imageHeight = 16;

    std::vector<Color> imageData;
    imageData.resize(manifest.imageWidth * manifest.imageHeight);

    Color black = {20, 20, 20, 255};
    Color white = {255, 255, 255, 255};

    for (uint32_t y = 0; y < manifest.imageHeight; ++y) {
        for (uint32_t x = 0; x < manifest.imageWidth; ++x) {
            if (x == 0 || x == manifest.imageWidth - 1 || y == 0 || y == manifest.imageHeight - 1) {
                imageData[y * manifest.imageWidth + x] = white;
            } else {
                imageData[y * manifest.imageWidth + x] = black;
            }
        }
    }

    // Calcular offsets
    header.manifestOffset = sizeof(UPM_Format::Header);
    header.imageDataOffset = header.manifestOffset + sizeof(UPM_Format::Manifest);

    // Escrever o ficheiro binário
    std::ofstream outFile("venom.upm", std::ios::binary);
    if (!outFile) {
        std::cerr << "Erro ao criar o ficheiro venom.upm" << std::endl;
        return 1;
    }

    outFile.write(reinterpret_cast<const char*>(&header), sizeof(header));
    outFile.write(reinterpret_cast<const char*>(&manifest), sizeof(manifest));
    outFile.write(reinterpret_cast<const char*>(imageData.data()), imageData.size() * sizeof(Color));

    outFile.close();

    std::cout << "Ficheiro 'venom.upm' gerado com sucesso." << std::endl;
    return 0;
}
