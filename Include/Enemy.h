#pragma once
#include "GameObject.h"

enum class EnemyState { Idle, Chase, Patrol, Dead };

class Enemy : public GameObject {
public:
  Enemy(DirectX::XMFLOAT2 position, float speed);

  void Update(float deltaTime) override;
  void Render(SpriteRenderer *renderer,
              const DirectX::XMMATRIX &viewProj) override;

  void SetTarget(GameObject *target) { m_target = target; }
  void TakeDamage();

  bool IsDead() const { return m_state == EnemyState::Dead; }

private:
  EnemyState m_state;
  float m_speed;
  GameObject *m_target;
  float m_health;
};
