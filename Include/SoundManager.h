#pragma once
#include <iostream>
#include <string>

class SoundManager {
public:
  static SoundManager &Instance() {
    static SoundManager instance;
    return instance;
  }

  void Init() { std::cout << "SoundManager Initialized" << std::endl; }

  // Placeholder for actual audio playback
  void Play(const std::string &effectName) {
    std::cout << "Playing Sound: " << effectName << std::endl;
  }

private:
  SoundManager() {}
};
