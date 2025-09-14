#pragma once

// Forward declarations
class SingularPixelObject;

class Animator {
public:
    // Aplica a animação de "pulsação" a um objeto.
    void ApplyWobble(SingularPixelObject& spo, float totalTime);
};
