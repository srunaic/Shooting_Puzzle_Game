#include "../Include/SpriteRenderer.h"
#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

SpriteRenderer::SpriteRenderer() : m_dxCore(nullptr) {}

SpriteRenderer::~SpriteRenderer() {}

bool SpriteRenderer::Initialize(DXCore *dxCore) {
  m_dxCore = dxCore;
  auto device = m_dxCore->GetDevice();

  // Vertex data for a quad
  Vertex vertices[] = {
      {{-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
      {{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
      {{-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
      {{1.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
  };

  D3D11_BUFFER_DESC vbd = {};
  vbd.Usage = D3D11_USAGE_DEFAULT;
  vbd.ByteWidth = sizeof(vertices);
  vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

  D3D11_SUBRESOURCE_DATA vsd = {vertices};
  device->CreateBuffer(&vbd, &vsd, m_vertexBuffer.GetAddressOf());

  // Shaders
  ID3DBlob *vsBlob = nullptr;
  D3DCompileFromFile(L"Assets/Shaders/Sprite.hlsl", nullptr, nullptr, "VS",
                     "vs_4_0", 0, 0, &vsBlob, nullptr);
  device->CreateVertexShader(vsBlob->GetBufferPointer(),
                             vsBlob->GetBufferSize(), nullptr,
                             m_vertexShader.GetAddressOf());

  D3D11_INPUT_ELEMENT_DESC ied[] = {
      {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
       D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,
       D3D11_INPUT_PER_VERTEX_DATA, 0},
  };
  device->CreateInputLayout(ied, 2, vsBlob->GetBufferPointer(),
                            vsBlob->GetBufferSize(),
                            m_inputLayout.GetAddressOf());
  vsBlob->Release();

  ID3DBlob *psBlob = nullptr;
  D3DCompileFromFile(L"Assets/Shaders/Sprite.hlsl", nullptr, nullptr, "PS",
                     "ps_4_0", 0, 0, &psBlob, nullptr);
  device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(),
                            nullptr, m_pixelShader.GetAddressOf());
  psBlob->Release();

  // Constant Buffer
  D3D11_BUFFER_DESC cbd = {};
  cbd.Usage = D3D11_USAGE_DYNAMIC;
  cbd.ByteWidth = sizeof(SpriteConstantBuffer);
  cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  device->CreateBuffer(&cbd, nullptr, m_constantBuffer.GetAddressOf());

  // Blend States
  D3D11_BLEND_DESC bd = {};
  bd.RenderTarget[0].BlendEnable = TRUE;
  bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
  bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  device->CreateBlendState(&bd, m_alphaBlendState.GetAddressOf());

  bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE; // Additive
  device->CreateBlendState(&bd, m_additiveBlendState.GetAddressOf());

  return true;
}

void SpriteRenderer::SetAdditiveBlend(bool enable) {
  auto context = m_dxCore->GetContext();
  if (enable)
    context->OMSetBlendState(m_additiveBlendState.Get(), nullptr, 0xFFFFFFFF);
  else
    context->OMSetBlendState(m_alphaBlendState.Get(), nullptr, 0xFFFFFFFF);
}

void SpriteRenderer::Draw(const XMMATRIX &transform, const XMFLOAT4 &color) {
  auto context = m_dxCore->GetContext();

  D3D11_MAPPED_SUBRESOURCE ms;
  context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
  SpriteConstantBuffer *cb = (SpriteConstantBuffer *)ms.pData;
  cb->worldViewProj = XMMatrixTranspose(transform);
  cb->color = color;
  context->Unmap(m_constantBuffer.Get(), 0);

  UINT stride = sizeof(Vertex);
  UINT offset = 0;
  context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride,
                              &offset);
  context->IASetInputLayout(m_inputLayout.Get());
  context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

  context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
  context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
  context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

  context->Draw(4, 0);
}
