#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
  Player();

  void Update(float deltaTime) override;
  void Render(SpriteRenderer *renderer,
              const DirectX::XMMATRIX &viewProj) override;

private:
  float m_speed;
};
