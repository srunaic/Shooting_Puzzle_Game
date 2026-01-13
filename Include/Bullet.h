#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:
  Bullet();

  void Fire(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 direction,
            float speed);
  void Update(float deltaTime) override;
  void Render(SpriteRenderer *renderer,
              const DirectX::XMMATRIX &viewProj) override;

  bool IsDead() const { return m_lifeTime <= 0; }
  void Reflect(DirectX::XMFLOAT2 normal);
  DirectX::XMFLOAT2 GetDirection() const { return m_direction; }

private:
  DirectX::XMFLOAT2 m_direction;
  float m_speed;
  float m_lifeTime;
};
