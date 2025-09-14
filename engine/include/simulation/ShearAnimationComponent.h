#pragma once

#include "world/Component.h"
#include <string>

class Animator; // Forward declaration

class ShearAnimationComponent : public Component {
public:
    // Construtor: recebe o nome da parte a animar e uma referência ao Animator
    ShearAnimationComponent(const std::string& partName, Animator& animator);

    void OnUpdate(float deltaTime, SingularPixelObject& owner) override;

private:
    std::string m_PartName;
    Animator& m_Animator;
    float m_TotalTime; // Cada componente pode ter o seu próprio estado
};
