#pragma once
#include <directxmath.h>

struct Rect {
  float x, y; // Center
  float width, height;

  float Left() const { return x - width / 2.0f; }
  float Right() const { return x + width / 2.0f; }
  float Top() const { return y + height / 2.0f; }
  float Bottom() const { return y - height / 2.0f; }
};

class Physics {
public:
  static bool IntersectAABB(const Rect &a, const Rect &b) {
    if (a.Right() < b.Left() || a.Left() > b.Right())
      return false;
    if (a.Top() < b.Bottom() || a.Bottom() > b.Top())
      return false;
    return true;
  }

  static DirectX::XMFLOAT2 Reflect(const DirectX::XMFLOAT2 &dir,
                                   const DirectX::XMFLOAT2 &normal) {
    // R = I - 2 * (I . N) * N
    float dot = dir.x * normal.x + dir.y * normal.y;
    return {dir.x - 2.0f * dot * normal.x, dir.y - 2.0f * dot * normal.y};
  }
};
