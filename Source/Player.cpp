#include "../Include/Player.h"
#include "../Include/Input.h"

using namespace DirectX;

Player::Player() : GameObject("Player"), m_speed(300.0f) {
  m_transform.scale = {50.0f, 50.0f};
}

void Player::Update(float deltaTime) {
  if (!m_active)
    return;

  auto &input = Input::Instance();
  XMFLOAT2 move = {0, 0};

  if (input.IsKeyDown('W'))
    move.y += 1.0f;
  if (input.IsKeyDown('S'))
    move.y -= 1.0f;
  if (input.IsKeyDown('A'))
    move.x -= 1.0f;
  if (input.IsKeyDown('D'))
    move.x += 1.0f;

  // Normalize and move
  if (move.x != 0 || move.y != 0) {
    float length = sqrt(move.x * move.x + move.y * move.y);
    m_transform.position.x += (move.x / length) * m_speed * deltaTime;
    m_transform.position.y += (move.y / length) * m_speed * deltaTime;
  }
}

void Player::Render(SpriteRenderer *renderer, const XMMATRIX &viewProj) {
  if (!m_active)
    return;

  XMMATRIX world = m_transform.GetWorldMatrix();
  XMMATRIX wvp = world * viewProj;

  renderer->Draw(wvp, XMFLOAT4(0, 1, 0, 1)); // Green player
}
