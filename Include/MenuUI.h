#pragma once
#include "UIObject.h"
#include <functional>
#include <vector>

struct MenuButton {
  std::string text;
  DirectX::XMFLOAT2 position;
  DirectX::XMFLOAT2 scale;
  std::function<void()> callback;
  bool isHovered;
};

class MainMenu : public UIObject {
public:
  MainMenu();
  void Update(float deltaTime) override;
  void Render(class SpriteRenderer *renderer,
              const DirectX::XMMATRIX &viewProj) override;

private:
  std::vector<MenuButton> m_buttons;
  int m_selectedIndex;
};

class PauseMenu : public UIObject {
public:
  PauseMenu();
  void Update(float deltaTime) override;
  void Render(class SpriteRenderer *renderer,
              const DirectX::XMMATRIX &viewProj) override;

private:
  std::vector<MenuButton> m_buttons;
};
