#include "../Include/HUD.h"
#include "../Include/SpriteRenderer.h"

using namespace DirectX;

// HealthHUD Implementation
HealthHUD::HealthHUD(int maxHealth)
    : UIObject("HealthHUD"), m_maxHealth(maxHealth), m_currentHealth(maxHealth),
      m_segmentWidth(0.05f), m_spacing(0.01f) {
  m_transform.position = {-0.9f, 0.9f};
}

void HealthHUD::Update(float deltaTime) {}

void HealthHUD::Render(SpriteRenderer *renderer, const XMMATRIX &viewProj) {
  if (!m_active)
    return;

  for (int i = 0; i < m_maxHealth; ++i) {
    XMMATRIX world = XMMatrixScaling(m_segmentWidth, 0.02f, 1.0f) *
                     XMMatrixTranslation(m_transform.position.x +
                                             (m_segmentWidth + m_spacing) * i,
                                         m_transform.position.y, 0.0f);

    XMFLOAT4 color = (i < m_currentHealth) ? XMFLOAT4(0.2f, 0.8f, 1.0f, 1.0f)
                                           : XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
    renderer->Draw(world, color);
  }
}

// ArrowTypeHUD Implementation
ArrowTypeHUD::ArrowTypeHUD() : UIObject("ArrowTypeHUD"), m_currentType(0) {
  m_transform.position = {-0.9f, 0.8f};
}

void ArrowTypeHUD::Render(SpriteRenderer *renderer, const XMMATRIX &viewProj) {
  if (!m_active)
    return;

  XMMATRIX bgWorld =
      XMMatrixScaling(0.04f, 0.04f, 1.0f) *
      XMMatrixTranslation(m_transform.position.x, m_transform.position.y, 0.0f);
  renderer->Draw(bgWorld, XMFLOAT4(0.1f, 0.1f, 0.2f, 0.8f));

  XMMATRIX iconWorld =
      XMMatrixScaling(0.02f, 0.02f, 1.0f) *
      XMMatrixTranslation(m_transform.position.x, m_transform.position.y, 0.0f);

  XMFLOAT4 color;
  switch (m_currentType) {
  case 0:
    color = {1.0f, 1.0f, 1.0f, 1.0f};
    break;
  case 1:
    color = {1.0f, 0.2f, 0.2f, 1.0f};
    break;
  case 2:
    color = {0.2f, 1.0f, 0.2f, 1.0f};
    break;
  default:
    color = {1.0f, 1.0f, 1.0f, 1.0f};
  }
  renderer->Draw(iconWorld, color);
}
