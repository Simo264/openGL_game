#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <GL/glew.h>
#include <vector>

class GameLevel
{
private:
  void init(std::vector<std::vector<uint32_t>> tileData, uint32_t levelWidth, uint32_t levelHeight);

public:
  // level state
  std::vector<class GameObject> bricks;

  // constructor
  GameLevel() { }
  
  // destructor
  ~GameLevel() { }

  // loads level from file
  void loadLevel(const char *file, uint32_t levelWidth, uint32_t levelHeight);

  // render level
  void renderLevel(class SpriteRenderer* renderer);

  // check if the level is completed (all non-solid tiles are destroyed)
  bool isCompleted();
};

#endif