#pragma once
#include <cstdint>

#pragma pack(push, 1)

namespace UPM_Format {

    struct Header {
        uint32_t magic;
        uint32_t version;
        uint32_t manifestOffset;
        uint32_t imageDataOffset;
        uint32_t bodyDataOffset;
        uint32_t componentDataOffset;
    };

    struct Manifest {
        uint32_t imageWidth;
        uint32_t imageHeight;
    };

    struct BodyPartHeader {
        char     name[32];
        uint32_t pixelCount;
    };

    struct PixelCoord {
        uint16_t x;
        uint16_t y;
    };
    
    struct ComponentDescriptor {
        uint32_t type;
        char     targetPart[32];
    };

} // namespace UPM_Format

#pragma pack(pop)
