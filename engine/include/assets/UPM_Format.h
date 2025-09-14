#pragma once
#include <cstdint>

#pragma pack(push, 1)

namespace UPM_Format {

    // O cabeçalho no início de cada ficheiro .upm
    struct Header {
        uint32_t magic;         // 'UPM '
        uint32_t version;       // Versão do formato
        uint32_t manifestOffset;  // Deslocamento para o bloco de manifesto
        uint32_t imageDataOffset; // Deslocamento para os dados da imagem
        uint32_t bodyDataOffset;  // NOVO: Deslocamento para os dados do corpo
    };

    // O manifesto contém metadados sobre o asset.
    struct Manifest {
        uint32_t imageWidth;
        uint32_t imageHeight;
    };

    // NOVO: Estrutura para os metadados de uma única parte do corpo no ficheiro.
    struct BodyPartHeader {
        char     name[32];       // Nome da parte (tamanho fixo de 32 bytes)
        uint32_t pixelCount;     // Quantos píxeis pertencem a esta parte
    };

    // NOVO: Estrutura para a coordenada de um pixel no ficheiro.
    // Usamos tipos menores para economizar espaço.
    struct PixelCoord {
        uint16_t x;
        uint16_t y;
    };


} // namespace UPM_Format

#pragma pack(pop)
