#include "../Include/UIManager.h"
#include "../Include/SpriteRenderer.h"

using namespace DirectX;

UIManager::UIManager()
    : m_flashAlpha(0), m_flashTimer(0), m_flashColor(1, 1, 1, 1) {}

UIManager::~UIManager() { Clear(); }

void UIManager::Update(float deltaTime) {
  if (m_flashTimer > 0) {
    m_flashTimer -= deltaTime;
    m_flashAlpha = m_flashTimer / 0.2f;
    if (m_flashAlpha < 0)
      m_flashAlpha = 0;
  }

  for (auto obj : m_uiObjects) {
    if (obj->IsActive())
      obj->Update(deltaTime);
  }
}

void UIManager::Render(SpriteRenderer *renderer) {
  XMMATRIX identity = XMMatrixIdentity();

  for (auto obj : m_uiObjects) {
    if (obj->IsActive())
      obj->Render(renderer, identity);
  }

  if (m_flashAlpha > 0) {
    XMFLOAT4 color = m_flashColor;
    color.w = m_flashAlpha * 0.5f;

    XMMATRIX scale = XMMatrixScaling(2.0f, 2.0f, 1.0f);
    renderer->Draw(scale, color);
  }
}

void UIManager::Clear() {
  for (auto obj : m_uiObjects) {
    delete obj;
  }
  m_uiObjects.clear();
}

void UIManager::TriggerFlash(XMFLOAT4 color, float duration) {
  m_flashColor = color;
  m_flashTimer = duration;
  m_flashAlpha = 1.0f;
}
