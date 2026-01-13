#pragma once
#include "GameObject.h"
#include <vector>

class LevelManager {
public:
  static LevelManager &Instance() {
    static LevelManager instance;
    return instance;
  }

  void Init();
  void Update(float deltaTime);
  void Render(class SpriteRenderer *renderer,
              const DirectX::XMMATRIX &viewProj);

  void AddObject(GameObject *obj) { m_objects.push_back(obj); }
  const std::vector<GameObject *> &GetObjects() const { return m_objects; }
  void Clear();

private:
  LevelManager();
  std::vector<GameObject *> m_objects;
};
