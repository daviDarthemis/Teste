#include "assets/UPM_Parser.h"
#include "assets/UPM_Format.h"
#include "world/SingularPixelObject.h"
#include <iostream>
#include <cstring>

std::unique_ptr<SingularPixelObject> UPM_Parser::Parse(const std::vector<char>& fileData) {
    if (fileData.size() < sizeof(UPM_Format::Header)) {
        std::cerr << "Erro de Parse UPM: Ficheiro demasiado pequeno para conter um cabeçalho." << std::endl;
        return nullptr;
    }

    const UPM_Format::Header* header = reinterpret_cast<const UPM_Format::Header*>(fileData.data());

    if (header->magic != 0x204D5055) {
        std::cerr << "Erro de Parse UPM: Número mágico inválido. Não é um ficheiro UPM." << std::endl;
        return nullptr;
    }

    if (header->version != 1) {
        std::cerr << "Erro de Parse UPM: Versão do ficheiro não suportada." << std::endl;
        return nullptr;
    }

    const UPM_Format::Manifest* manifest = reinterpret_cast<const UPM_Format::Manifest*>(fileData.data() + header->manifestOffset);
    int width = manifest->imageWidth;
    int height = manifest->imageHeight;

    auto spo = std::make_unique<SingularPixelObject>(width, height);

    const char* imageDataPtr = fileData.data() + header->imageDataOffset;
    size_t imageDataSize = width * height * sizeof(Vector4);

    if (header->imageDataOffset + imageDataSize > fileData.size()) {
        std::cerr << "Erro de Parse UPM: Os dados da imagem excedem o tamanho do ficheiro." << std::endl;
        return nullptr;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            const uint8_t* pixelSrc = reinterpret_cast<const uint8_t*>(imageDataPtr) + (index * 4);
            Vector4 color = {pixelSrc[0], pixelSrc[1], pixelSrc[2], pixelSrc[3]};
            spo->SetBasePixel(x, y, color);
        }
    }

    std::cout << "Asset UPM carregado com sucesso: " << width << "x" << height << std::endl;
    return spo;
}
