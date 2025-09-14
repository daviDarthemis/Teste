#include "simulation/ShearAnimationComponent.h"
#include "simulation/Animator.h"
#include "world/SingularPixelObject.h"

ShearAnimationComponent::ShearAnimationComponent(const std::string& partName, Animator& animator)
    : m_PartName(partName), m_Animator(animator), m_TotalTime(0.0f) {
}

void ShearAnimationComponent::OnUpdate(float deltaTime, SingularPixelObject& owner) {
    // Acumula o tempo que passa
    m_TotalTime += deltaTime;
    
    // Chama a lógica do Animator
    m_Animator.ApplyShear(owner, m_PartName, m_TotalTime);
}
