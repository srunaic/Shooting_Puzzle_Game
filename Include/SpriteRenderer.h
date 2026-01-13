#pragma once
#include "DXCore.h"
#include <d3dcompiler.h>
#include <vector>

struct Vertex {
  DirectX::XMFLOAT3 position;
  DirectX::XMFLOAT2 texcoord;
};

struct SpriteConstantBuffer {
  DirectX::XMMATRIX worldViewProj;
  DirectX::XMFLOAT4 color;
};

class SpriteRenderer {
public:
  SpriteRenderer();
  ~SpriteRenderer();

  bool Initialize(DXCore *dxCore);
  void Draw(const DirectX::XMMATRIX &transform, const DirectX::XMFLOAT4 &color);
  void SetAdditiveBlend(bool enable);

private:
  DXCore *m_dxCore;
  ComPtr<ID3D11Buffer> m_vertexBuffer;
  ComPtr<ID3D11Buffer> m_constantBuffer;
  ComPtr<ID3D11VertexShader> m_vertexShader;
  ComPtr<ID3D11PixelShader> m_pixelShader;
  ComPtr<ID3D11InputLayout> m_inputLayout;
  ComPtr<ID3D11BlendState> m_alphaBlendState;
  ComPtr<ID3D11BlendState> m_additiveBlendState;
};
