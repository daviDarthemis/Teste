#pragma once

#include "world/Component.h"
#include <string>

class Animator; // Forward declaration

class WobbleAnimationComponent : public Component {
public:
    // Construtor: recebe o nome da parte (embora o wobble seja global por enquanto) e uma referência ao Animator
    WobbleAnimationComponent(const std::string& partName, Animator& animator);

    void OnUpdate(float deltaTime, SingularPixelObject& owner) override;

private:
    std::string m_PartName;
    Animator& m_Animator;
    float m_TotalTime;
};
