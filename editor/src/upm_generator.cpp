#include "assets/UPM_Format.h"
#include "vendor/FastNoiseLite.h"
#include "core/Types.h" // <<<--- ESTA É A CORREÇÃO FUNDAMENTAL
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>

struct Color { uint8_t r, g, b, a; };

int main() {
    std::cout << "Gerador de UPM v2.1 (com Tentáculos Processuais)" << std::endl;

    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
    srand(time(NULL));
    noise.seed = rand(); 
    noise.frequency = 0.1f;
    float noiseThreshold = 0.0f;

    UPM_Format::Header header;
    header.magic = 0x204D5055;
    header.version = 1;

    UPM_Format::Manifest manifest;
    manifest.imageWidth = 16;
    manifest.imageHeight = 16;
    
    std::vector<Color> imageData(manifest.imageWidth * manifest.imageHeight, {0,0,0,0});
    Color black = {20, 20, 20, 255};
    Color white = {255, 255, 255, 255};
    Color red = {200, 30, 30, 255};

    UPM_Format::BodyPartHeader corePartHeader;
    std::vector<UPM_Format::PixelCoord> corePartPixels;

    for (uint16_t y = 0; y < manifest.imageHeight; ++y) {
        for (uint16_t x = 0; x < manifest.imageWidth; ++x) {
            float noiseValue = fnlGetNoise2D(&noise, (float)x, (float)y);
            if (noiseValue > noiseThreshold) {
                imageData[y * manifest.imageWidth + x] = black;
                corePartPixels.push_back({x, y});
            }
        }
    }
    strncpy(corePartHeader.name, "core", 32);
    corePartHeader.pixelCount = corePartPixels.size();

    const int numTentacleSegments = 4;
    const int segmentLength = 3;
    std::vector<UPM_Format::BodyPartHeader> tentaclePartHeaders(numTentacleSegments);
    std::vector<std::vector<UPM_Format::PixelCoord>> tentaclePixels(numTentacleSegments);

    Vector2i anchorPoint = {-1, -1};
    int bestX = 0;
    for (const auto& p : corePartPixels) {
        if (p.x > bestX) {
            bestX = p.x;
            anchorPoint = {(int)p.x, (int)p.y};
        }
    }

    if (anchorPoint.x != -1) {
        Vector2i currentPos = anchorPoint;
        for (int i = 0; i < numTentacleSegments; ++i) {
            std::string partName = "tentacle_" + std::to_string(i);
            strncpy(tentaclePartHeaders[i].name, partName.c_str(), 32);

            for (int j = 0; j < segmentLength; ++j) {
                int dx = 0, dy = 0;
                int r = rand() % 10;
                if (r < 6) dx = 1;
                else if (r < 8) dy = 1;
                else dy = -1;

                Vector2i nextPos = {currentPos.x + dx, currentPos.y + dy};

                if (nextPos.x >= 0 && nextPos.x < manifest.imageWidth && 
                    nextPos.y >= 0 && nextPos.y < manifest.imageHeight &&
                    imageData[nextPos.y * manifest.imageWidth + nextPos.x].a == 0)
                {
                    currentPos = nextPos;
                    imageData[currentPos.y * manifest.imageWidth + currentPos.x] = red;
                    tentaclePixels[i].push_back({(uint16_t)currentPos.x, (uint16_t)currentPos.y});
                }
            }
            tentaclePartHeaders[i].pixelCount = tentaclePixels[i].size();
        }
    }
    
    std::vector<UPM_Format::ComponentDescriptor> components;
    components.push_back({2, "core"});
    components.push_back({3, "tentacle_"});

    size_t imageDataSize = imageData.size() * sizeof(Color);
    size_t corePartDataSize = sizeof(corePartHeader) + (corePartPixels.size() * sizeof(UPM_Format::PixelCoord));
    size_t allTentaclesDataSize = 0;
    for(int i = 0; i < numTentacleSegments; ++i) {
        allTentaclesDataSize += sizeof(tentaclePartHeaders[i]) + (tentaclePixels[i].size() * sizeof(UPM_Format::PixelCoord));
    }
    size_t bodyDataSize = sizeof(uint32_t) + corePartDataSize + allTentaclesDataSize;
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

    uint32_t partCount = 1 + numTentacleSegments;
    outFile.write(reinterpret_cast<const char*>(&partCount), sizeof(partCount));
    outFile.write(reinterpret_cast<const char*>(&corePartHeader), sizeof(corePartHeader));
    outFile.write(reinterpret_cast<const char*>(corePartPixels.data()), corePartPixels.size() * sizeof(UPM_Format::PixelCoord));

    for(int i = 0; i < numTentacleSegments; ++i) {
        outFile.write(reinterpret_cast<const char*>(&tentaclePartHeaders[i]), sizeof(tentaclePartHeaders[i]));
        outFile.write(reinterpret_cast<const char*>(tentaclePixels[i].data()), tentaclePixels[i].size() * sizeof(UPM_Format::PixelCoord));
    }

    uint32_t componentCount = components.size();
    outFile.write(reinterpret_cast<const char*>(&componentCount), sizeof(componentCount));
    outFile.write(reinterpret_cast<const char*>(components.data()), componentDataSize);

    outFile.close();
    std::cout << "Ficheiro 'venom.upm' com núcleo e tentáculo processuais gerado com sucesso." << std::endl;
    return 0;
}
