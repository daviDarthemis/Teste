#pragma once
#include <cstdint> // Para tipos de inteiros de tamanho fixo como uint32_t

// Instrui o compilador para alinhar as estruturas em limites de 1 byte.
// Essencial para garantir que o layout em memória corresponde exatamente ao layout no ficheiro.
#pragma pack(push, 1)

namespace UPM_Format {

    // O cabeçalho no início de cada ficheiro .upm
    struct Header {
        uint32_t magic;      // Número mágico para identificar o ficheiro ('UPM ' em little-endian)
        uint32_t version;    // Versão do formato do ficheiro (ex: 1)
        uint32_t manifestOffset; // Deslocamento em bytes para o início do bloco de manifesto
        uint32_t imageDataOffset; // Deslocamento para o início dos dados da imagem
        // (Offsets para outros blocos virão aqui no futuro)
    };

    // O manifesto contém metadados sobre o asset.
    struct Manifest {
        uint32_t imageWidth;
        uint32_t imageHeight;
        // (Número de animações, etc., virá aqui)
    };

    // O bloco de dados de imagem não precisa de uma estrutura,
    // pois serão apenas bytes RGBA em sequência.

} // namespace UPM_Format

// Restaura as configurações de alinhamento padrão do compilador.
#pragma pack(pop)
