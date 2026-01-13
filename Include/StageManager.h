#pragma once
#include <string>
#include <vector>


enum class GameState { LevelStart, Playing, Win, GameOver };

class StageManager {
public:
  static StageManager &Instance() {
    static StageManager instance;
    return instance;
  }

  void Init();
  void Update(float deltaTime);
  void Render(class SpriteRenderer *renderer,
              const DirectX::XMMATRIX &viewProj);

  void LoadLevel(int levelIndex);
  void RestartLevel();
  void NextLevel();

  GameState GetState() const { return m_state; }

private:
  StageManager();
  GameState m_state;
  int m_currentLevel;
  float m_stateTimer;
};
