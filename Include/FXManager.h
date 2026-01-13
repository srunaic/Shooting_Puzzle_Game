#pragma once
#include "GameObject.h"
#include <vector>

struct LightTrail {
  DirectX::XMFLOAT2 start;
  DirectX::XMFLOAT2 end;
  float alpha;
  float lifeTime;
};

class FXManager {
public:
  static FXManager &Instance() {
    static FXManager instance;
    return instance;
  }

  void Update(float deltaTime);
  void Render(class SpriteRenderer *renderer,
              const DirectX::XMMATRIX &viewProj);

  void AddTrail(DirectX::XMFLOAT2 start, DirectX::XMFLOAT2 end);

private:
  FXManager();
  std::vector<LightTrail> m_trails;
};
