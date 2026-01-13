#pragma once
#include <directxmath.h>

class Camera {
public:
  Camera(float width, float height);

  void Update();

  DirectX::XMMATRIX GetViewMatrix() const { return m_viewMatrix; }
  DirectX::XMMATRIX GetProjectionMatrix() const { return m_projectionMatrix; }
  DirectX::XMMATRIX GetViewProjectionMatrix() const {
    return DirectX::XMMatrixMultiply(m_viewMatrix, m_projectionMatrix);
  }

  void SetPosition(float x, float y) { m_position = {x, y, -10.0f}; }
  DirectX::XMFLOAT3 GetPosition() const { return m_position; }

private:
  DirectX::XMFLOAT3 m_position;
  DirectX::XMMATRIX m_viewMatrix;
  DirectX::XMMATRIX m_projectionMatrix;
};
