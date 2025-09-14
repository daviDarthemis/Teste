#pragma once

#include <string>
#include <memory>
#include <map>

// Apenas precisamos de ponteiros (shared_ptr) para SingularPixelObject,
// então uma forward declaration é a abordagem correta e mais segura aqui.
class SingularPixelObject; 

class AssetManager {
public:
    std::shared_ptr<SingularPixelObject> LoadSPO(const std::string& filePath);

private:
    std::map<std::string, std::shared_ptr<SingularPixelObject>> m_SpoCache;
};
