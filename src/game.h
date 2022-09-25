#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>

// Represents the current state of the game
enum GameState { 
  GAME_ACTIVE, 
  GAME_MENU, 
  GAME_WIN 
};

class Game
{
public:
  GameState state;

  bool keys[1024];
  
  uint32_t width;
  uint32_t height;

  Game(uint32_t w, uint32_t h);
  ~Game();

  // initialize game state (load all shaders/textures/levels)
  void init();

  // game loop
  void processInput(float deltaTime);
  void update(float deltaTime);
  void render();
};

#endif