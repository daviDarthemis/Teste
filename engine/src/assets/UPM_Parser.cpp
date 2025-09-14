#include "assets/UPM_Parser.h"
#include "assets/UPM_Format.h"
#include "world/SingularPixelObject.h"
#include <iostream>
#include <cstring> // Para memcpy

std::unique_ptr<SingularPixelObject> UPM_Parser::Parse(const std::vector<char>& fileData) {
    if (fileData.size() < sizeof(UPM_Format::Header)) {
        std::cerr << "Erro de Parse UPM: Ficheiro demasiado pequeno para conter um cabeçalho." << std::endl;
        return nullptr;
    }

    // 1. Ler e validar o Cabeçalho
    const UPM_Format::Header* header = reinterpret_cast<const UPM_Format::Header*>(fileData.data());

    if (header->magic != 0x204D5055) {
        std::cerr << "Erro de Parse UPM: Número mágico inválido. Não é um ficheiro UPM." << std::endl;
        return nullptr;
    }

    if (header->version != 1) {
        std::cerr << "Erro de Parse UPM: Versão do ficheiro não suportada." << std::endl;
        return nullptr;
    }

    // 2. Ler o Manifesto
    const UPM_Format::Manifest* manifest = reinterpret_cast<const UPM_Format::Manifest*>(fileData.data() + header->manifestOffset);
    int width = manifest->imageWidth;
    int height = manifest->imageHeight;

    // 3. Criar o SPO
    auto spo = std::make_unique<SingularPixelObject>(width, height);

    // 4. Ler os dados da Imagem
    const char* imageDataPtr = fileData.data() + header->imageDataOffset;
    size_t imageDataSize = width * height * sizeof(Vector4);

    // Validação de segurança para evitar ler fora dos limites do ficheiro
    if (header->imageDataOffset + imageDataSize > fileData.size()) {
        std::cerr << "Erro de Parse UPM: Os dados da imagem excedem o tamanho do ficheiro." << std::endl;
        return nullptr;
    }

    // Copia os dados de pixel diretamente para o vetor do SPO.
    // Isto é extremamente rápido. O Vector4 (r,g,b,a) tem o mesmo layout de memória que a nossa cor no gerador.
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            const uint8_t* pixelSrc = reinterpret_cast<const uint8_t*>(imageDataPtr) + (index * 4);
            Vector4 color = {pixelSrc[0], pixelSrc[1], pixelSrc[2], pixelSrc[3]};
            spo->SetPixel(x, y, color);
        }
    }

    std::cout << "Asset UPM carregado com sucesso: " << width << "x" << height << std::endl;
    return spo;
}
