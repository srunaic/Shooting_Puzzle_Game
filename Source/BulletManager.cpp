#include "../Include/BulletManager.h"
#include "../Include/Enemy.h"
#include "../Include/LevelManager.h"
#include "../Include/Mirror.h"
#include "../Include/Physics.h"


BulletManager::BulletManager() {}

void BulletManager::Initialize(int poolSize) {
  for (int i = 0; i < poolSize; ++i) {
    m_bullets.push_back(new Bullet());
  }
}

void BulletManager::Fire(DirectX::XMFLOAT2 position,
                         DirectX::XMFLOAT2 direction, float speed) {
  for (auto bullet : m_bullets) {
    if (!bullet->IsActive()) {
      bullet->Fire(position, direction, speed);
      return;
    }
  }
}

void BulletManager::Update(float deltaTime) {
  auto &levelObjects = LevelManager::Instance().GetObjects();

  for (auto bullet : m_bullets) {
    if (!bullet->IsActive())
      continue;

    bullet->Update(deltaTime);

    // Collision with level objects (mirrors, enemies, etc.)
    for (auto obj : levelObjects) {
      if (!obj->IsActive())
        continue;

      Rect br = {bullet->GetTransform().position.x,
                 bullet->GetTransform().position.y, 10, 10};

      Mirror *mirror = dynamic_cast<Mirror *>(obj);
      if (mirror) {
        Rect mr = {mirror->GetTransform().position.x,
                   mirror->GetTransform().position.y,
                   mirror->GetTransform().scale.x,
                   mirror->GetTransform().scale.y};

        if (Physics::IntersectAABB(br, mr)) {
          bullet->Reflect(mirror->GetNormal());
          bullet->Update(0.01f);
        }
      }

      Enemy *enemy = dynamic_cast<Enemy *>(obj);
      if (enemy) {
        Rect er = {
            enemy->GetTransform().position.x, enemy->GetTransform().position.y,
            enemy->GetTransform().scale.x, enemy->GetTransform().scale.y};

        if (Physics::IntersectAABB(br, er)) {
          enemy->TakeDamage();
          bullet->SetActive(false); // Bullet consumed
        }
      }
    }
  }
}

void BulletManager::Render(SpriteRenderer *renderer,
                           const DirectX::XMMATRIX &viewProj) {
  for (auto bullet : m_bullets) {
    if (bullet->IsActive()) {
      bullet->Render(renderer, viewProj);
    }
  }
}
