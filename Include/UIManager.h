#pragma once
#include <directxmath.h>

class UIManager {
public:
  static UIManager &Instance() {
    static UIManager instance;
    return instance;
  }

  void Update(float deltaTime);
  void Render(class SpriteRenderer *renderer);

  void ShowLevelStart(int level);
  void ShowWin();
  void ShowGameOver();

  void TriggerFlash(DirectX::XMFLOAT4 color, float duration);

private:
  UIManager();
  float m_flashAlpha;
  float m_flashTimer;
  DirectX::XMFLOAT4 m_flashColor;
};
