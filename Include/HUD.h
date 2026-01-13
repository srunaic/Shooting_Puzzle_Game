#pragma once
#include "UIObject.h"

class HealthHUD : public UIObject {
public:
  HealthHUD(int maxHealth);
  void Update(float deltaTime) override;
  void Render(class SpriteRenderer *renderer,
              const DirectX::XMMATRIX &viewProj) override;

  void SetCurrentHealth(int health) { m_currentHealth = health; }

private:
  int m_maxHealth;
  int m_currentHealth;
  float m_segmentWidth;
  float m_spacing;
};

class ArrowTypeHUD : public UIObject {
public:
  ArrowTypeHUD();
  void Render(class SpriteRenderer *renderer,
              const DirectX::XMMATRIX &viewProj) override;

  void SetArrowType(int type) { m_currentType = type; }

private:
  int m_currentType;
};
