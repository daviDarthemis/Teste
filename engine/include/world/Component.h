#pragma once

// Forward declaration para evitar dependência circular
class SingularPixelObject;

// A interface base para todos os componentes.
class Component {
public:
    // O destrutor virtual é OBRIGATÓRIO para classes base com funções virtuais.
    virtual ~Component() = default;

    // Chamado a cada frame. `owner` é a entidade à qual este componente está anexado.
    virtual void OnUpdate(float deltaTime, SingularPixelObject& owner) = 0;

protected:
    // O construtor é protegido para que apenas classes derivadas possam ser criadas.
    Component() = default;
};
