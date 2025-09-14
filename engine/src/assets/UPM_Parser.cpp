#include "assets/UPM_Parser.h"
#include "assets/UPM_Format.h"
#include "world/SingularPixelObject.h"
#include <iostream>
#include <cstring>

std::unique_ptr<SingularPixelObject> UPM_Parser::Parse(const std::vector<char>& fileData) {
    if (fileData.size() < sizeof(UPM_Format::Header)) {
        std::cerr << "Erro de Parse UPM: Ficheiro demasiado pequeno." << std::endl; return nullptr;
    }
    const UPM_Format::Header* header = reinterpret_cast<const UPM_Format::Header*>(fileData.data());

    if (header->magic != 0x204D5055) {
        std::cerr << "Erro de Parse UPM: Número mágico inválido." << std::endl; return nullptr;
    }
    if (header->version != 1) {
        std::cerr << "Erro de Parse UPM: Versão não suportada." << std::endl; return nullptr;
    }

    const UPM_Format::Manifest* manifest = reinterpret_cast<const UPM_Format::Manifest*>(fileData.data() + header->manifestOffset);
    int width = manifest->imageWidth;
    int height = manifest->imageHeight;
    auto spo = std::make_unique<SingularPixelObject>(width, height);

    const char* imageDataPtr = fileData.data() + header->imageDataOffset;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            const uint8_t* pixelSrc = reinterpret_cast<const uint8_t*>(imageDataPtr) + (index * 4);
            spo->SetBasePixel(x, y, {pixelSrc[0], pixelSrc[1], pixelSrc[2], pixelSrc[3]});
        }
    }
    
    // --- NOVO: Parsing do Bloco de Corpo ---
    const char* bodyDataPtr = fileData.data() + header->bodyDataOffset;
    uint32_t partCount = *reinterpret_cast<const uint32_t*>(bodyDataPtr);
    bodyDataPtr += sizeof(uint32_t);

    for (uint32_t i = 0; i < partCount; ++i) {
        const UPM_Format::BodyPartHeader* partHeader = reinterpret_cast<const UPM_Format::BodyPartHeader*>(bodyDataPtr);
        bodyDataPtr += sizeof(UPM_Format::BodyPartHeader);
        
        BodyPart newPart;
        newPart.name = std::string(partHeader->name);

        for (uint32_t p = 0; p < partHeader->pixelCount; ++p) {
            const UPM_Format::PixelCoord* coord = reinterpret_cast<const UPM_Format::PixelCoord*>(bodyDataPtr);
            bodyDataPtr += sizeof(UPM_Format::PixelCoord);
            newPart.pixelCoordinates.push_back({static_cast<int>(coord->x), static_cast<int>(coord->y)});
        }
        spo->GetBodyParts().push_back(newPart);
    }

    return spo;
}
