#include "../Include/GameObject.h"
#include "../Include/SpriteRenderer.h"

using namespace DirectX;

GameObject::GameObject(const std::string &name)
    : m_name(name), m_active(true) {}

GameObject::~GameObject() {}

void GameObject::Update(float deltaTime) {}

void GameObject::Render(SpriteRenderer *renderer, const XMMATRIX &viewProj) {
  if (!m_active)
    return;

  XMMATRIX world = m_transform.GetWorldMatrix();
  XMMATRIX wvp = world * viewProj;

  renderer->Draw(wvp, XMFLOAT4(1, 1, 1, 1)); // Default white color
}
