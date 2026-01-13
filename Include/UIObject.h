#pragma once
#include "GameObject.h"

class UIObject : public GameObject {
public:
  UIObject(const std::string &name);
  virtual ~UIObject();

  // UI elements match GameObject signature but ignore viewProj for identity
  // rendering
  virtual void Render(class SpriteRenderer *renderer,
                      const DirectX::XMMATRIX &viewProj) override;

  void SetColor(DirectX::XMFLOAT4 color) { m_color = color; }
  DirectX::XMFLOAT4 GetColor() const { return m_color; }

protected:
  DirectX::XMFLOAT4 m_color;
};
