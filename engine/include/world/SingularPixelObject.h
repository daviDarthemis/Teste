#pragma once

#include "core/Types.h"
#include "world/Body.h"
#include "world/ComponentFactory.h"
#include <vector>
#include <memory>

class Component;

class SingularPixelObject {
public:
    SingularPixelObject(int width, int height);
    ~SingularPixelObject();

    void SetBasePixel(int x, int y, const Vector4& color);
    const Vector4& GetBasePixel(int x, int y) const;
    const std::vector<Vector4>& GetBasePixelData() const;
    std::vector<Vector4>& GetDeformedPixelData();

    void SetPosition(const Vector2f& position);
    const Vector2f& GetPosition() const;
    const Vector2i& GetSize() const;

    std::vector<BodyPart>& GetBodyParts();
    const std::vector<BodyPart>& GetBodyParts() const;

    // Modificado para aceitar um std::unique_ptr<Component>
    void AddComponent(std::unique_ptr<Component> component);
    
    void UpdateComponents(float deltaTime);

    std::vector<ComponentRequest>& GetComponentRequests();

private:
    Vector2f m_Position;
    Vector2i m_Size;
    
    std::vector<Vector4> m_BasePixelData;
    std::vector<Vector4> m_DeformedPixelData;
    std::vector<BodyPart> m_BodyParts;
    
    std::vector<std::unique_ptr<Component>> m_Components;
    std::vector<ComponentRequest> m_ComponentRequests;
};
