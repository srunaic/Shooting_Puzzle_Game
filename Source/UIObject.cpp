#include "../Include/UIObject.h"
#include "../Include/SpriteRenderer.h"

using namespace DirectX;

UIObject::UIObject(const std::string &name)
    : GameObject(name), m_color(1, 1, 1, 1) {}

UIObject::~UIObject() {}

void UIObject::Render(SpriteRenderer *renderer, const XMMATRIX &viewProj) {
  if (!m_active)
    return;

  // UI objects ignore viewProj and use identity because they are in screen
  // space
  XMMATRIX world = m_transform.GetWorldMatrix();

  renderer->Draw(world, m_color);
}
