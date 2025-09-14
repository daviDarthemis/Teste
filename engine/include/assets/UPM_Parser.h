#pragma once

#include <memory>
#include <vector>

class SingularPixelObject;

class UPM_Parser {
public:
    // Agora recebe um ponteiro para os dados binários e o seu tamanho.
    static std::unique_ptr<SingularPixelObject> Parse(const std::vector<char>& fileData);
};
