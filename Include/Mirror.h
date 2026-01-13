#pragma once
#include "GameObject.h"

class Mirror : public GameObject {
public:
  Mirror(DirectX::XMFLOAT2 position, float rotation, DirectX::XMFLOAT2 scale);

  void Update(float deltaTime) override;
  void Render(SpriteRenderer *renderer,
              const DirectX::XMMATRIX &viewProj) override;

  DirectX::XMFLOAT2 GetNormal() const;
};
