#include "../Include/SpriteRenderer.h"

SpriteRenderer::SpriteRenderer() : m_dxCore(nullptr) {}

SpriteRenderer::~SpriteRenderer() {}

bool SpriteRenderer::Initialize(DXCore *dxCore) {
  m_dxCore = dxCore;
  auto device = m_dxCore->GetDevice();

  // Shaders
  ComPtr<ID3DBlob> vsBlob, psBlob, errorBlob;
  HRESULT hr =
      D3DCompileFromFile(L"Assets/Shaders/Sprite.hlsl", nullptr, nullptr, "VS",
                         "vs_5_0", 0, 0, &vsBlob, &errorBlob);
  if (FAILED(hr))
    return false;
  hr = D3DCompileFromFile(L"Assets/Shaders/Sprite.hlsl", nullptr, nullptr, "PS",
                          "ps_5_0", 0, 0, &psBlob, &errorBlob);
  if (FAILED(hr))
    return false;

  device->CreateVertexShader(vsBlob->GetBufferPointer(),
                             vsBlob->GetBufferSize(), nullptr, &m_vertexShader);
  device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(),
                            nullptr, &m_pixelShader);

  // Input Layout
  D3D11_INPUT_ELEMENT_DESC ied[] = {{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
                                     0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                                    {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
                                     12, D3D11_INPUT_PER_VERTEX_DATA, 0}};
  device->CreateInputLayout(ied, 2, vsBlob->GetBufferPointer(),
                            vsBlob->GetBufferSize(), &m_inputLayout);

  // Quad Vertices (NDC -1 to 1)
  Vertex vertices[] = {{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}},
                       {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}},
                       {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}},
                       {{0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}}};

  D3D11_BUFFER_DESC vbd = {};
  vbd.Usage = D3D11_USAGE_DEFAULT;
  vbd.ByteWidth = sizeof(vertices);
  vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

  D3D11_SUBRESOURCE_DATA vsd = {vertices};
  device->CreateBuffer(&vbd, &vsd, &m_vertexBuffer);

  // Constant Buffer
  D3D11_BUFFER_DESC cbd = {};
  cbd.Usage = D3D11_USAGE_DYNAMIC;
  cbd.ByteWidth = sizeof(SpriteConstantBuffer);
  cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  device->CreateBuffer(&cbd, nullptr, &m_constantBuffer);

  return true;
}

void SpriteRenderer::Draw(const DirectX::XMMATRIX &transform,
                          const DirectX::XMFLOAT4 &color) {
  auto context = m_dxCore->GetContext();

  // Update Constant Buffer
  D3D11_MAPPED_SUBRESOURCE mappedResource;
  context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0,
               &mappedResource);
  SpriteConstantBuffer *data = (SpriteConstantBuffer *)mappedResource.pData;
  data->worldViewProj = DirectX::XMMatrixTranspose(transform);
  data->color = color;
  context->Unmap(m_constantBuffer.Get(), 0);

  // Set Pipeline
  UINT stride = sizeof(Vertex);
  UINT offset = 0;
  context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride,
                              &offset);
  context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
  context->IASetInputLayout(m_inputLayout.Get());
  context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
  context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
  context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

  context->Draw(4, 0);
}
