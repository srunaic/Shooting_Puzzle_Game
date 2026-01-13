#pragma once
#include <directxmath.h>
#include <string>

struct Transform {
  DirectX::XMFLOAT2 position;
  float rotation;
  DirectX::XMFLOAT2 scale;

  Transform() : position(0, 0), rotation(0), scale(1, 1) {}

  DirectX::XMMATRIX GetWorldMatrix() const {
    return DirectX::XMMatrixScaling(scale.x, scale.y, 1.0f) *
           DirectX::XMMatrixRotationZ(rotation) *
           DirectX::XMMatrixTranslation(position.x, position.y, 0.0f);
  }
};

class GameObject {
public:
  GameObject(const std::string &name);
  virtual ~GameObject();

  virtual void Update(float deltaTime);
  virtual void Render(class SpriteRenderer *renderer,
                      const DirectX::XMMATRIX &viewProj);

  Transform &GetTransform() { return m_transform; }
  const std::string &GetName() const { return m_name; }

  void SetActive(bool active) { m_active = active; }
  bool IsActive() const { return m_active; }

protected:
  std::string m_name;
  Transform m_transform;
  bool m_active;
};
