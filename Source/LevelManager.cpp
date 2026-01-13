#include "../Include/LevelManager.h"
#include "../Include/Enemy.h"
#include "../Include/Mirror.h"


LevelManager::LevelManager() {}

void LevelManager::Init() {}

void LevelManager::Clear() {
  for (auto obj : m_objects) {
    delete obj;
  }
  m_objects.clear();
}

void LevelManager::Update(float deltaTime) {
  for (auto obj : m_objects) {
    if (obj->IsActive())
      obj->Update(deltaTime);
  }
}

void LevelManager::Render(SpriteRenderer *renderer,
                          const DirectX::XMMATRIX &viewProj) {
  for (auto obj : m_objects) {
    if (obj->IsActive())
      obj->Render(renderer, viewProj);
  }
}
