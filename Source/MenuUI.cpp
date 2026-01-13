#include "../Include/MenuUI.h"
#include "../Include/Input.h"
#include "../Include/SpriteRenderer.h"
#include "../Include/StageManager.h"


using namespace DirectX;

// MainMenu Implementation
MainMenu::MainMenu() : UIObject("MainMenu"), m_selectedIndex(0) {
  m_buttons.push_back({"START",
                       {0, 0.2f},
                       {0.2f, 0.05f},
                       []() { /* Start logic handled by StageManager */ },
                       false});
  m_buttons.push_back({"OPTIONS", {0, 0.0f}, {0.2f, 0.05f}, []() {}, false});
  m_buttons.push_back(
      {"EXIT", {0, -0.2f}, {0.2f, 0.05f}, []() { PostQuitMessage(0); }, false});
}

void MainMenu::Update(float deltaTime) {
  // Basic mouse interaction
  auto &input = Input::Instance();
  // In a real game, we'd check mouse pos against button rects.
  // For now, simple keyboard navigation
  if (input.IsKeyDown(VK_UP)) {
    m_selectedIndex =
        (m_selectedIndex > 0) ? m_selectedIndex - 1 : (int)m_buttons.size() - 1;
  }
  if (input.IsKeyDown(VK_DOWN)) {
    m_selectedIndex =
        (m_selectedIndex < m_buttons.size() - 1) ? m_selectedIndex + 1 : 0;
  }

  for (int i = 0; i < m_buttons.size(); ++i)
    m_buttons[i].isHovered = (i == m_selectedIndex);
}

void MainMenu::Render(SpriteRenderer *renderer, const XMMATRIX &viewProj) {
  if (!m_active)
    return;

  // Background darken
  renderer->Draw(XMMatrixScaling(2.0f, 2.0f, 1.0f), XMFLOAT4(0, 0, 0.1f, 0.5f));

  for (int i = 0; i < m_buttons.size(); ++i) {
    XMFLOAT4 color = m_buttons[i].isHovered ? XMFLOAT4(0.4f, 1.0f, 1.0f, 1.0f)
                                            : XMFLOAT4(0.2f, 0.5f, 0.6f, 0.8f);
    XMMATRIX world =
        XMMatrixScaling(m_buttons[i].scale.x, m_buttons[i].scale.y, 1.0f) *
        XMMatrixTranslation(m_buttons[i].position.x, m_buttons[i].position.y,
                            0.0f);
    renderer->Draw(world, color);
  }
}

// PauseMenu Implementation
PauseMenu::PauseMenu() : UIObject("PauseMenu") {
  m_buttons.push_back({"RESUME", {0, 0.1f}, {0.2f, 0.05f}, []() {}, false});
  m_buttons.push_back(
      {"QUIT", {0, -0.1f}, {0.2f, 0.05f}, []() { PostQuitMessage(0); }, false});
}

void PauseMenu::Update(float deltaTime) {}

void PauseMenu::Render(SpriteRenderer *renderer, const XMMATRIX &viewProj) {
  if (!m_active)
    return;

  renderer->Draw(XMMatrixScaling(1.0f, 1.0f, 1.0f), XMFLOAT4(0, 0, 0, 0.7f));

  for (auto &btn : m_buttons) {
    XMMATRIX world = XMMatrixScaling(btn.scale.x, btn.scale.y, 1.0f) *
                     XMMatrixTranslation(btn.position.x, btn.position.y, 0.0f);
    renderer->Draw(world, XMFLOAT4(0.6f, 0.6f, 0.7f, 1.0f));
  }
}
