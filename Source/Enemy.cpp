#include "../Include/Enemy.h"

using namespace DirectX;

Enemy::Enemy(XMFLOAT2 position, float speed)
    : GameObject("Enemy"), m_state(EnemyState::Idle), m_speed(speed),
      m_target(nullptr), m_health(1.0f) {
  m_transform.position = position;
  m_transform.scale = {40.0f, 40.0f};
}

void Enemy::Update(float deltaTime) {
  if (m_state == EnemyState::Dead || !m_active)
    return;

  if (m_target && m_state == EnemyState::Chase) {
    XMFLOAT2 targetPos = m_target->GetTransform().position;
    float dx = targetPos.x - m_transform.position.x;
    float dy = targetPos.y - m_transform.position.y;
    float len = sqrt(dx * dx + dy * dy);

    if (len > 5.0f) {
      m_transform.position.x += (dx / len) * m_speed * deltaTime;
      m_transform.position.y += (dy / len) * m_speed * deltaTime;
    }
  } else if (m_target) {
    // Simple detection range
    XMFLOAT2 targetPos = m_target->GetTransform().position;
    float dx = targetPos.x - m_transform.position.x;
    float dy = targetPos.y - m_transform.position.y;
    float len = sqrt(dx * dx + dy * dy);

    if (len < 400.0f) {
      m_state = EnemyState::Chase;
    }
  }
}

void Enemy::Render(SpriteRenderer *renderer, const XMMATRIX &viewProj) {
  if (!m_active)
    return;

  XMMATRIX world = m_transform.GetWorldMatrix();
  XMMATRIX wvp = world * viewProj;

  // Red color for enemies
  XMFLOAT4 color = {1.0f, 0.2f, 0.2f, 1.0f};
  if (m_state == EnemyState::Dead)
    color.w = 0.5f;

  renderer->Draw(wvp, color);
}

void Enemy::TakeDamage() {
  m_health -= 1.0f;
  if (m_health <= 0) {
    m_state = EnemyState::Dead;
    m_active = false; // For now just deactivate
  }
}
