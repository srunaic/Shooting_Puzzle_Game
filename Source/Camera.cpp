#include "../Include/Camera.h"

using namespace DirectX;

Camera::Camera(float width, float height) : m_position(0.0f, 0.0f, -10.0f) {
  // Orthographic projection for 2D
  m_projectionMatrix = XMMatrixOrthographicLH(width, height, 0.1f, 1000.0f);
  Update();
}

void Camera::Update() {
  XMVECTOR eye = XMLoadFloat3(&m_position);
  XMVECTOR target = XMVectorSet(m_position.x, m_position.y, 0.0f, 0.0f);
  XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

  m_viewMatrix = XMMatrixLookAtLH(eye, target, up);
}
