#include "world/World.h"
#include "world/SingularPixelObject.h"
#include "simulation/Animator.h" // Incluir o Animator para ter acesso ao filtro

void World::AddEntity(std::shared_ptr<SingularPixelObject> entity) {
    m_Entities.push_back(entity);
}

void World::Update(float deltaTime, Animator& animator) { // O World agora precisa de uma referência ao Animator
    for (auto& entity : m_Entities) {
        // PASSO 1: Preparar o frame
        entity->GetDeformedPixelData() = entity->GetBasePixelData();

        // PASSO 2: Executar componentes de animação
        entity->UpdateComponents(deltaTime);

        // PASSO 3 (NOVO): Aplicar filtros de pós-processamento
        animator.ApplyGooeyFilter(*entity);
    }
}

const std::vector<std::shared_ptr<SingularPixelObject>>& World::GetEntities() const {
    return m_Entities;
}
