#pragma once
#include "UIObject.h"
#include <vector>

class UIManager {
public:
  static UIManager &Instance() {
    static UIManager instance;
    return instance;
  }

  void Update(float deltaTime);
  void Render(class SpriteRenderer *renderer);

  void AddUIObject(UIObject *obj) { m_uiObjects.push_back(obj); }
  void Clear();

  void ShowLevelStart(int level);
  void ShowWin();
  void ShowGameOver();

  void TriggerFlash(DirectX::XMFLOAT4 color, float duration);

private:
  UIManager();
  ~UIManager();

  float m_flashAlpha;
  float m_flashTimer;
  DirectX::XMFLOAT4 m_flashColor;

  std::vector<UIObject *> m_uiObjects;
};
