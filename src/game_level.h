#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "shader.h"
#include "game_object.h"

#include <vector>
#include <cstdint>

class GameLevel
{
private:
  // loads level from file
  void load(const char* file, uint32_t levelWidth, uint32_t levelHeight);
  
  // initialize level from tile data
  void init(std::vector<std::vector<uint32_t>> tileData, uint32_t levelWidth, uint32_t levelHeight);

  void clear();

public:
  // level state
  std::vector<GameObject*> objects;
  
  // constructor
  GameLevel(const char* file, uint32_t levelWidth, uint32_t levelHeight);
  
  // render level
  void render(Shader* shader);
  
  // check if the level is completed (all non-solid tiles are destroyed)
  bool isCompleted();
};

#endif