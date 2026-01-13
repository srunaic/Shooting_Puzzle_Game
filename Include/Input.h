#pragma once
#include <vector>
#include <windows.h>


class Input {
public:
  static Input &Instance() {
    static Input instance;
    return instance;
  }

  void Update();

  bool IsKeyDown(int key) const { return m_keyState[key]; }
  bool IsKeyJustPressed(int key) const {
    return m_keyState[key] && !m_prevKeyState[key];
  }

  void SetKeyDown(int key, bool down) { m_keyState[key] = down; }

  POINT GetMousePosition() const { return m_mousePos; }
  void SetMousePosition(int x, int y) {
    m_mousePos.x = x;
    m_mousePos.y = y;
  }

private:
  Input();
  bool m_keyState[256];
  bool m_prevKeyState[256];
  POINT m_mousePos;
};
