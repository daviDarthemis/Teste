#pragma once

#include "assets/UPM_Format.h" // Incluir para ComponentDescriptor
#include <string>
#include <memory>
#include <vector>

class Component;
class Animator;
class SingularPixelObject;

// Estrutura que guarda o pedido para criar um componente, lido do ficheiro.
struct ComponentRequest {
    uint32_t type;
    std::string targetPart;
};

// A "Fábrica" que sabe como construir componentes a partir de pedidos.
class ComponentFactory {
public:
    static std::unique_ptr<Component> Create(const ComponentRequest& request, Animator& animator);
};
