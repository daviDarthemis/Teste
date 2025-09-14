#include "world/ComponentFactory.h"
#include "simulation/ShearAnimationComponent.h"
#include "simulation/WobbleAnimationComponent.h"
#include "simulation/WaveAnimationComponent.h" // Incluir o novo componente
#include <iostream>

std::unique_ptr<Component> ComponentFactory::Create(const ComponentRequest& request, Animator& animator) {
    switch (request.type) {
        case 1: // ID para ShearAnimationComponent (agora obsoleto, mas mantido)
            return std::make_unique<ShearAnimationComponent>(request.targetPart, animator);
        
        case 2: // ID para WobbleAnimationComponent
            return std::make_unique<WobbleAnimationComponent>(request.targetPart, animator);
        
        case 3: // NOVO: ID para WaveAnimationComponent
            return std::make_unique<WaveAnimationComponent>(request.targetPart, animator);
            
        default:
            std::cerr << "Aviso: Tipo de componente desconhecido no ficheiro: " << request.type << std::endl;
            return nullptr;
    }
}
