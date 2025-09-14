#pragma once
#include <string> // Necessário para std::string

// Forward declarations
class SingularPixelObject;

class Animator {
public:
    // Animação de "pulsação" global
    void ApplyWobble(SingularPixelObject& spo, float totalTime);

    // NOVO: Animação de "cisalhamento" para uma parte específica
    void ApplyShear(SingularPixelObject& spo, const std::string& partName, float totalTime);
};
