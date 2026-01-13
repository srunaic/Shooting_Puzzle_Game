#include "../Include/UIManager.h"
#include "../Include/SpriteRenderer.h"

using namespace DirectX;

UIManager::UIManager()
    : m_flashAlpha(0), m_flashTimer(0), m_flashColor(1, 1, 1, 1) {}

void UIManager::Update(float deltaTime) {
  if (m_flashTimer > 0) {
    m_flashTimer -= deltaTime;
    m_flashAlpha = m_flashTimer / 0.2f; // Fade out based on 0.2s flash
    if (m_flashAlpha < 0)
      m_flashAlpha = 0;
  }
}

void UIManager::Render(SpriteRenderer *renderer) {
  if (m_flashAlpha > 0) {
    // Screen-space overlay (identity matrix for NDC -1 to 1)
    XMMATRIX identity = XMMatrixIdentity();
    XMFLOAT4 color = m_flashColor;
    color.w = m_flashAlpha * 0.5f; // Semi-transparent

    // Large quad covering the screen
    XMMATRIX scale = XMMatrixScaling(2.0f, 2.0f, 1.0f);
    renderer->Draw(scale, color);
  }
}

void UIManager::TriggerFlash(XMFLOAT4 color, float duration) {
  m_flashColor = color;
  m_flashTimer = duration;
  m_flashAlpha = 1.0f;
}
