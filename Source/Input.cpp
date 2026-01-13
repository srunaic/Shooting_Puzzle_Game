#include "../Include/Input.h"
#include <cstring>

Input::Input() {
  memset(m_keyState, 0, sizeof(m_keyState));
  memset(m_prevKeyState, 0, sizeof(m_prevKeyState));
  m_mousePos = {0, 0};
}

void Input::Update() { memcpy(m_prevKeyState, m_keyState, sizeof(m_keyState)); }
