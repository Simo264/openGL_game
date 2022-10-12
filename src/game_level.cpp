#include "game_level.h"
#include "game_object.h"
#include "resource_manager.h"

#include <glm/glm.hpp>

#include <string>
#include <sstream>
#include <fstream>

void GameLevel::loadLevel(const char *file, uint32_t levelWidth, uint32_t levelHeight)
{
  /*
    1 1 1 1 1 1 
    2 2 0 0 2 2
    3 3 4 4 3 3
  */

  // clear old data
  bricks.clear();

  // load from file
  std::ifstream fstream(file);
  std::vector<std::vector<uint32_t>> tileData;
  
  if (fstream)
  {
    std::string line;

    // read each line from level file
    while (std::getline(fstream, line)) 
    {
      std::istringstream sstream(line);
      std::vector<uint32_t> row;
      
      // read each word separated by spaces
      uint32_t tileCode;
      while (sstream >> tileCode) 
        row.push_back(tileCode);
      
      tileData.push_back(row);
    }

    if (tileData.size() > 0)
      init(tileData, levelWidth, levelHeight);
  }

}

// render level
void GameLevel::renderLevel(class SpriteRenderer* renderer)
{

}

// check if the level is completed (all non-solid tiles are destroyed)
bool GameLevel::isCompleted()
{
  return false;
}

void GameLevel::init(std::vector<std::vector<uint32_t>> tileData, uint32_t levelWidth, uint32_t levelHeight)
{
  // calculate dimensions
  const uint32_t height = tileData.size();
  const uint32_t width = tileData[0].size();
  
  // cube size
  float unit_width = levelWidth / static_cast<float>(width);
  float unit_height = levelHeight / height;

  // initialize level tiles based on tileData
  for (uint32_t y = 0; y < height; ++y)
  {
    for (uint32_t x = 0; x < width; ++x)
    {
      const glm::vec2 pos(unit_width * x, unit_height * y);
      const glm::vec2 size(unit_width, unit_height);
      glm::vec3 color = glm::vec3(1.f);
      Texture2D* texture = nullptr;
      bool solid = false;

      if (tileData[y][x] == 0) 
        continue;

      else if (tileData[y][x] == 1) 
      {
        texture = ResourceManager::getTexture("block_solid");
        color = glm::vec3(0.8f, 0.8f, 0.7f);
        solid = true;
      }

      else
      {
        texture = ResourceManager::getTexture("block");

        if (tileData[y][x] == 2)
          color = glm::vec3(0.2f, 0.6f, 1.0f);
        else if (tileData[y][x] == 3)
          color = glm::vec3(0.0f, 0.7f, 0.0f);
        else if (tileData[y][x] == 4)
          color = glm::vec3(0.8f, 0.8f, 0.4f);
        else if (tileData[y][x] == 5)
          color = glm::vec3(1.0f, 0.5f, 0.0f);
      }
      
      GameObject obj(pos, size, texture, color);
      obj.isSolid = solid;
      bricks.push_back(obj);
    }
  }  
}