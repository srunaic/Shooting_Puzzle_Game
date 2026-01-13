#pragma once
#include "Bullet.h"
#include <vector>

class BulletManager {
public:
  static BulletManager &Instance() {
    static BulletManager instance;
    return instance;
  }

  void Initialize(int poolSize);
  void Fire(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 direction,
            float speed);

  void Update(float deltaTime);
  void Render(SpriteRenderer *renderer, const DirectX::XMMATRIX &viewProj);

  std::vector<Bullet *> &GetBullets() { return m_bullets; }

private:
  BulletManager();
  std::vector<Bullet *> m_bullets;
};
