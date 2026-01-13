#include "../Include/StageManager.h"
#include "../Include/BulletManager.h"
#include "../Include/Enemy.h"
#include "../Include/HUD.h"
#include "../Include/Input.h"
#include "../Include/LevelManager.h"
#include "../Include/MenuUI.h"
#include "../Include/Mirror.h"
#include "../Include/Player.h"
#include "../Include/UIManager.h"
#include <memory>


extern std::unique_ptr<Player> g_player;

StageManager::StageManager()
    : m_state(GameState::MainMenu), m_currentLevel(1), m_stateTimer(0) {}

void StageManager::Init() {
  // Start with Main Menu
  UIManager::Instance().Clear();
  UIManager::Instance().AddUIObject(new MainMenu());
}

void StageManager::LoadLevel(int levelIndex) {
  m_currentLevel = levelIndex;
  m_state = GameState::LevelStart;
  m_stateTimer = 2.0f;

  LevelManager::Instance().Clear();
  UIManager::Instance().Clear();

  // HUD
  UIManager::Instance().AddUIObject(new HealthHUD(5));
  UIManager::Instance().AddUIObject(new ArrowTypeHUD());

  // Setup player
  g_player->GetTransform().position = {-500, 0};
  g_player->SetActive(true);

  if (levelIndex == 1) {
    LevelManager::Instance().AddObject(new Mirror({0, 0}, 0.785f, {150, 20}));
    LevelManager::Instance().AddObject(new Enemy({400, 200}, 100.0f));
    ((Enemy *)LevelManager::Instance().GetObjects().back())
        ->SetTarget(g_player.get());
  } else if (levelIndex == 2) {
    LevelManager::Instance().AddObject(
        new Mirror({100, 100}, 0.785f, {150, 20}));
    LevelManager::Instance().AddObject(
        new Mirror({-100, -100}, -0.785f, {150, 20}));
    LevelManager::Instance().AddObject(new Enemy({300, 0}, 120.0f));
    LevelManager::Instance().AddObject(new Enemy({0, 300}, 120.0f));
    for (auto obj : LevelManager::Instance().GetObjects()) {
      Enemy *e = dynamic_cast<Enemy *>(obj);
      if (e)
        e->SetTarget(g_player.get());
    }
  }
}

void StageManager::Update(float deltaTime) {
  auto &input = Input::Instance();

  if (m_state == GameState::MainMenu) {
    if (input.IsKeyDown(VK_RETURN)) {
      LoadLevel(1);
    }
  } else if (m_state == GameState::Paused) {
    if (input.IsKeyDown('P') || input.IsKeyDown(VK_ESCAPE)) {
      m_state = GameState::Playing;
      UIManager::Instance().Clear();
      UIManager::Instance().AddUIObject(new HealthHUD(5));
      UIManager::Instance().AddUIObject(new ArrowTypeHUD());
    }
  } else if (m_state == GameState::LevelStart) {
    m_stateTimer -= deltaTime;
    if (m_stateTimer <= 0)
      m_state = GameState::Playing;
  } else if (m_state == GameState::Playing) {
    if (input.IsKeyDown('P')) {
      m_state = GameState::Paused;
      UIManager::Instance().AddUIObject(new PauseMenu());
    }

    // Check win condition
    bool enemiesLeft = false;
    for (auto obj : LevelManager::Instance().GetObjects()) {
      if (dynamic_cast<Enemy *>(obj) && obj->IsActive()) {
        enemiesLeft = true;
        break;
      }
    }

    if (!enemiesLeft) {
      m_state = GameState::Win;
      m_stateTimer = 3.0f;
    }
  } else if (m_state == GameState::Win) {
    m_stateTimer -= deltaTime;
    if (m_stateTimer <= 0)
      NextLevel();
  }
}

void StageManager::NextLevel() {
  m_currentLevel++;
  LoadLevel(m_currentLevel);
}

void StageManager::RestartLevel() { LoadLevel(m_currentLevel); }
