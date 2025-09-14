#include "assets/AssetManager.h"
#include "assets/UPM_Parser.h"
#include "world/SingularPixelObject.h" // A definição completa é necessária aqui.
#include <fstream>
#include <iostream>
#include <vector>

std::shared_ptr<SingularPixelObject> AssetManager::LoadSPO(const std::string& filePath) {
    if (m_SpoCache.count(filePath)) {
        return m_SpoCache[filePath];
    }

    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o ficheiro de asset: " << filePath << std::endl;
        return nullptr;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        std::cerr << "Erro ao ler o ficheiro de asset: " << filePath << std::endl;
        return nullptr;
    }

    file.close();

    std::unique_ptr<SingularPixelObject> parsedSpo = UPM_Parser::Parse(buffer);

    if (parsedSpo) {
        m_SpoCache[filePath] = std::move(parsedSpo);
        return m_SpoCache[filePath];
    }

    return nullptr;
}
