#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <wrl.h>

using namespace Microsoft::WRL;

class DXCore
{
public:
    DXCore();
    ~DXCore();

    bool Initialize(HWND hWnd, int width, int height);
    void Shutdown();

    void BeginFrame(float r, float g, float b, float a);
    void EndFrame();

    ID3D11Device* GetDevice() { return m_device.Get(); }
    ID3D11DeviceContext* GetContext() { return m_deviceContext.Get(); }

private:
    ComPtr<ID3D11Device> m_device;
    ComPtr<ID3D11DeviceContext> m_deviceContext;
    ComPtr<IDXGISwapChain> m_swapChain;
    ComPtr<ID3D11RenderTargetView> m_renderTargetView;
    ComPtr<ID3D11DepthStencilView> m_depthStencilView;
    ComPtr<ID3D11Texture2D> m_depthStencilBuffer;

    D3D_FEATURE_LEVEL m_featureLevel;
};
