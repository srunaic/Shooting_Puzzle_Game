#define WIN32_LEAN_AND_MEAN
#include "../Include/BulletManager.h"
#include "../Include/Camera.h"
#include "../Include/DXCore.h"
#include "../Include/Input.h"
#include "../Include/LevelManager.h"
#include "../Include/Player.h"
#include "../Include/SoundManager.h"
#include "../Include/SpriteRenderer.h"
#include "../Include/StageManager.h"
#include "../Include/Timer.h"
#include "../Include/UIManager.h"
#include <memory>
#include <windows.h>


// Global objects
HWND g_hWnd = nullptr;
std::unique_ptr<DXCore> g_dxCore;
std::unique_ptr<Timer> g_timer;
std::unique_ptr<SpriteRenderer> g_renderer;
std::unique_ptr<Camera> g_camera;
std::unique_ptr<Player> g_player;

// Window Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
  switch (message) {
  case WM_LBUTTONDOWN:
    Input::Instance().SetKeyDown(VK_LBUTTON, true);
    break;
  case WM_LBUTTONUP:
    Input::Instance().SetKeyDown(VK_LBUTTON, false);
    break;
  case WM_KEYDOWN:
    Input::Instance().SetKeyDown((int)wParam, true);
    break;
  case WM_KEYUP:
    Input::Instance().SetKeyDown((int)wParam, false);
    break;
  case WM_MOUSEMOVE:
    Input::Instance().SetMousePosition(LOWORD(lParam), HIWORD(lParam));
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  WNDCLASSEX wc = {};
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WndProc;
  wc.hInstance = hInstance;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.lpszClassName = L"PrismArcherWindowClass";
  RegisterClassEx(&wc);

  RECT wr = {0, 0, 1280, 720};
  AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

  g_hWnd = CreateWindowEx(0, L"PrismArcherWindowClass", L"Prism Archer",
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                          wr.right - wr.left, wr.bottom - wr.top, nullptr,
                          nullptr, hInstance, nullptr);

  if (!g_hWnd)
    return -1;
  ShowWindow(g_hWnd, nCmdShow);

  // Initialize systems
  g_dxCore = std::make_unique<DXCore>();
  g_dxCore->Initialize(g_hWnd, 1280, 720);

  g_timer = std::make_unique<Timer>();
  g_timer->Reset();

  g_renderer = std::make_unique<SpriteRenderer>();
  g_renderer->Initialize(g_dxCore.get());

  g_camera = std::make_unique<Camera>(1280, 720);
  g_player = std::make_unique<Player>();

  BulletManager::Instance().Initialize(50);
  SoundManager::Instance().Init();
  StageManager::Instance().Init();

  // Main Game Loop
  MSG msg = {};
  while (msg.message != WM_QUIT) {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    } else {
      g_timer->Tick();
      Input::Instance().Update();
      float dt = g_timer->GetDeltaTime();

      // Update
      StageManager::Instance().Update(dt);
      g_player->Update(dt);
      LevelManager::Instance().Update(dt);
      BulletManager::Instance().Update(dt);
      UIManager::Instance().Update(dt);
      g_camera->Update();

      // Render
      g_dxCore->BeginFrame(0.1f, 0.1f, 0.2f, 1.0f);

      DirectX::XMMATRIX viewProj = g_camera->GetViewProjectionMatrix();
      LevelManager::Instance().Render(g_renderer.get(), viewProj);
      g_player->Render(g_renderer.get(), viewProj);
      BulletManager::Instance().Render(g_renderer.get(), viewProj);

      // UI Rendered on top
      UIManager::Instance().Render(g_renderer.get());

      if (Input::Instance().IsKeyDown(VK_ESCAPE))
        PostQuitMessage(0);

      g_dxCore->EndFrame();
    }
  }

  return (int)msg.wParam;
}
