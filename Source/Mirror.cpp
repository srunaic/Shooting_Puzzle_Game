#include "../Include/Mirror.h"
#include "../Include/SpriteRenderer.h"

using namespace DirectX;

Mirror::Mirror(XMFLOAT2 position, float rotation, XMFLOAT2 scale)
    : GameObject("Mirror") {
  m_transform.position = position;
  m_transform.rotation = rotation;
  m_transform.scale = scale;
}

void Mirror::Update(float deltaTime) {}

void Mirror::Render(SpriteRenderer *renderer, const XMMATRIX &viewProj) {
  if (!m_active)
    return;

  XMMATRIX world = m_transform.GetWorldMatrix();
  XMMATRIX wvp = world * viewProj;

  renderer->Draw(wvp, XMFLOAT4(0.5f, 0.8f, 1.0f, 1.0f)); // Light blue mirror
}

DirectX::XMFLOAT2 Mirror::GetNormal() const {
  // Normal vector based on rotation (0 = faces up/positive Y)
  // We'll assume the mirror faces one side of the thin quad
  float nx = -sin(m_transform.rotation);
  float ny = cos(m_transform.rotation);
  return {nx, ny};
}
