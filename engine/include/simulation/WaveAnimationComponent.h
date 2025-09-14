#pragma once

#include "world/Component.h"
#include "world/Body.h" // <<<--- CORREÇÃO 1: Incluir a definição de BodyPart
#include <string>
#include <vector>

class Animator;

class WaveAnimationComponent : public Component {
public:
    WaveAnimationComponent(const std::string& partPrefix, Animator& animator);
    void OnUpdate(float deltaTime, SingularPixelObject& owner) override;

private:
    std::string m_PartPrefix;
    Animator& m_Animator;
    float m_TotalTime;
    // O compilador agora sabe o que é BodyPart.
    std::vector<BodyPart*> m_TargetPartsCache;
};
