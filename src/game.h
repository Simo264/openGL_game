#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <memory>


// Represents the current state of the game
enum GameState { 
  GAME_ACTIVE, 
  GAME_MENU, 
  GAME_WIN 
};

class Game
{
private:
  std::unique_ptr<class SpriteRenderer> m_ptrRenderer;

public:
  GameState state;

  bool keys[1024];
  
  uint32_t width;
  uint32_t height;

  Game(uint32_t width, uint32_t height);
  ~Game();

  // initialize game state (load all shaders/textures/levels)
  void init();

  // game loop
  void processInput(float deltaTime);
  void update(float deltaTime);
  void render();
};

#endif