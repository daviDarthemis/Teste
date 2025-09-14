#pragma once

#include <vector>
#include <memory>

class SingularPixelObject;
class Animator; // Forward declaration

class World {
public:
    void AddEntity(std::shared_ptr<SingularPixelObject> entity);

    // Assinatura atualizada
    void Update(float deltaTime, Animator& animator);

    const std::vector<std::shared_ptr<SingularPixelObject>>& GetEntities() const;

private:
    std::vector<std::shared_ptr<SingularPixelObject>> m_Entities;
};
