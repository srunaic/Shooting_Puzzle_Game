#include "../Include/Bullet.h"
#include "../Include/Physics.h"
#include "../Include/SpriteRenderer.h"

using namespace DirectX;

Bullet::Bullet()
    : GameObject("Bullet"), m_direction(0, 0), m_speed(0), m_lifeTime(0) {
  m_transform.scale = {10.0f, 10.0f};
  m_active = false;
}

void Bullet::Fire(XMFLOAT2 position, XMFLOAT2 direction, float speed) {
  m_transform.position = position;
  m_direction = direction;
  m_speed = speed;
  m_lifeTime = 5.0f;
  m_active = true;
}

void Bullet::Update(float deltaTime) {
  if (!m_active)
    return;

  m_transform.position.x += m_direction.x * m_speed * deltaTime;
  m_transform.position.y += m_direction.y * m_speed * deltaTime;

  m_lifeTime -= deltaTime;
  if (m_lifeTime <= 0) {
    m_active = false;
  }
}

void Bullet::Render(SpriteRenderer *renderer, const XMMATRIX &viewProj) {
  if (!m_active)
    return;

  XMMATRIX world = m_transform.GetWorldMatrix();
  XMMATRIX wvp = world * viewProj;

  renderer->Draw(wvp, XMFLOAT4(1, 1, 0, 1));
}

// Added method for reflection
void Bullet::Reflect(DirectX::XMFLOAT2 normal) {
  m_direction = Physics::Reflect(m_direction, normal);
}
