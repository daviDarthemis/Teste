#include "simulation/WobbleAnimationComponent.h"
#include "simulation/Animator.h"
#include "world/SingularPixelObject.h"

WobbleAnimationComponent::WobbleAnimationComponent(const std::string& partName, Animator& animator)
    : m_PartName(partName), m_Animator(animator), m_TotalTime(0.0f) {
}

void WobbleAnimationComponent::OnUpdate(float deltaTime, SingularPixelObject& owner) {
    m_TotalTime += deltaTime;
    
    // Agora passa o nome da parte alvo
    m_Animator.ApplyWobble(owner, m_PartName, m_TotalTime);
}
