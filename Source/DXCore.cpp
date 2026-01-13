#include "../Include/DXCore.h"

DXCore::DXCore() : m_featureLevel(D3D_FEATURE_LEVEL_11_0) {}

DXCore::~DXCore() { Shutdown(); }

bool DXCore::Initialize(HWND hWnd, int width, int height) {
  DXGI_SWAP_CHAIN_DESC scd = {};
  scd.BufferCount = 1;
  scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  scd.BufferDesc.Width = width;
  scd.BufferDesc.Height = height;
  scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  scd.OutputWindow = hWnd;
  scd.SampleDesc.Count = 1;
  scd.Windowed = TRUE;
  scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

  UINT createDeviceFlags = 0;
#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

  HRESULT hr = D3D11CreateDeviceAndSwapChain(
      nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0,
      D3D11_SDK_VERSION, &scd, &m_swapChain, &m_device, &m_featureLevel,
      &m_deviceContext);

  if (FAILED(hr))
    return false;

  // Render Target View
  ComPtr<ID3D11Texture2D> backBuffer;
  m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);
  m_device->CreateRenderTargetView(backBuffer.Get(), nullptr,
                                   &m_renderTargetView);

  // Depth Stencil
  D3D11_TEXTURE2D_DESC dbd = {};
  dbd.Width = width;
  dbd.Height = height;
  dbd.MipLevels = 1;
  dbd.ArraySize = 1;
  dbd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  dbd.SampleDesc.Count = 1;
  dbd.Usage = D3D11_USAGE_DEFAULT;
  dbd.BindFlags = D3D11_BIND_DEPTH_STENCIL;

  m_device->CreateTexture2D(&dbd, nullptr, &m_depthStencilBuffer);
  m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), nullptr,
                                   &m_depthStencilView);

  m_deviceContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(),
                                      m_depthStencilView.Get());

  // Viewport
  D3D11_VIEWPORT vp = {};
  vp.Width = (float)width;
  vp.Height = (float)height;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  m_deviceContext->RSSetViewports(1, &vp);

  return true;
}

void DXCore::Shutdown() {
  // ComPtr handles cleanup
}

void DXCore::BeginFrame(float r, float g, float b, float a) {
  float color[4] = {r, g, b, a};
  m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), color);
  m_deviceContext->ClearDepthStencilView(
      m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f,
      0);
}

void DXCore::EndFrame() { m_swapChain->Present(1, 0); }
