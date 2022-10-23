#ifndef GAME_H
#define GAME_H

#include "game_level.h"
#include <cstdint>

enum GameState { 
  GAME_ACTIVE, 
  GAME_MENU, 
  GAME_WIN 
};

class Game
{
private:
  void doCollisions();

public:
  GameState state;

  bool keys[1024];
  
  uint32_t width;
  uint32_t height;

  std::vector<GameLevel> levels;
  uint32_t currentLevel;

  Game(uint32_t width_, uint32_t height_);

  // initialize game state (load all shaders/textures/levels)
  void init();

  // game loop
  void processInput(float deltaTime);
  void update(float deltaTime);
  void render();
};

#endif