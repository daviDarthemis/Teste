#include "simulation/WaveAnimationComponent.h"
#include "simulation/Animator.h"
#include "world/SingularPixelObject.h"

WaveAnimationComponent::WaveAnimationComponent(const std::string& partPrefix, Animator& animator)
    : m_PartPrefix(partPrefix), m_Animator(animator), m_TotalTime(0.0f) {
}

void WaveAnimationComponent::OnUpdate(float deltaTime, SingularPixelObject& owner) {
    m_TotalTime += deltaTime;
    
    // Preenche o cache na primeira execução
    if (m_TargetPartsCache.empty()) {
        for (auto& part : owner.GetBodyParts()) {
            if (part.name.rfind(m_PartPrefix, 0) == 0) { // Verifica se a string começa com o prefixo
                m_TargetPartsCache.push_back(&part);
            }
        }
    }

    // Aplica a animação de onda a cada parte encontrada
    for (size_t i = 0; i < m_TargetPartsCache.size(); ++i) {
        BodyPart* part = m_TargetPartsCache[i];
        // O atraso é proporcional ao índice do segmento na cadeia
        float phaseDelay = static_cast<float>(i) * 0.5f; // Ajuste este valor para mudar a "flexibilidade"
        m_Animator.ApplyShear(owner, part->name, m_TotalTime + phaseDelay);
    }
}
