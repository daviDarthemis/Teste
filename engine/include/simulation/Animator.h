#pragma once
#include <string>

class SingularPixelObject;

class Animator {
public:
    void ApplyWobble(SingularPixelObject& spo, const std::string& partName, float totalTime);
    void ApplyShear(SingularPixelObject& spo, const std::string& partName, float totalTime);

    // NOVO: O filtro de pós-processamento
    void ApplyGooeyFilter(SingularPixelObject& spo);
};
