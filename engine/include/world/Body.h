#pragma once

#include "core/Types.h"
#include <string>
#include <vector>

// Representação em memória de uma única parte do corpo.
struct BodyPart {
    std::string name;
    std::vector<Vector2i> pixelCoordinates;
};
