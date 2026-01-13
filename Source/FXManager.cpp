#include "../Include/FXManager.h"
#include "../Include/SpriteRenderer.h"

using namespace DirectX;

FXManager::FXManager() {}

void FXManager::Update(float deltaTime) {
  for (auto it = m_trails.begin(); it != m_trails.end();) {
    it->lifeTime -= deltaTime;
    it->alpha = it->lifeTime / 0.5f;
    if (it->lifeTime <= 0)
      it = m_trails.erase(it);
    else
      ++it;
  }
}

void FXManager::Render(SpriteRenderer *renderer, const XMMATRIX &viewProj) {
  renderer->SetAdditiveBlend(true);

  for (const auto &trail : m_trails) {
    // Simple line representation using a thin stretched quad
    XMFLOAT2 dir = {trail.end.x - trail.start.x, trail.end.y - trail.start.y};
    float len = sqrt(dir.x * dir.x + dir.y * dir.y);
    float angle = atan2(dir.y, dir.x);

    XMMATRIX world = XMMatrixScaling(len * 0.5f, 2.0f, 1.0f) *
                     XMMatrixRotationZ(angle) *
                     XMMatrixTranslation(trail.start.x + dir.x * 0.5f,
                                         trail.start.y + dir.y * 0.5f, 0.0f);

    renderer->Draw(world * viewProj, XMFLOAT4(0.4f, 0.9f, 1.0f, trail.alpha));
  }

  renderer->SetAdditiveBlend(false);
}

void FXManager::AddTrail(XMFLOAT2 start, XMFLOAT2 end) {
  m_trails.push_back({start, end, 1.0f, 0.5f});
}
