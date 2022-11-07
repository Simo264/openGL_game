#include "game_level.h"
#include "resource_manager.h"

#include <fstream>
#include <sstream>
#include <GL/glew.h>

GameLevel::GameLevel(const char* file, uint32_t levelWidth, uint32_t levelHeight)
{
  load(file, levelWidth, levelHeight);
}

// loads level from file
void GameLevel::load(const char* file, uint32_t levelWidth, uint32_t levelHeight)
{
  // clear old data
  clear();
  
  // load from file
  uint32_t tileCode;
  std::ifstream fstream(file);

  if (fstream)
  {
    std::vector<std::vector<uint32_t>> tileData;
    
    std::string line;
    while (std::getline(fstream, line)) // read each line from level file
    {
      std::istringstream sstream(line);
      std::vector<uint32_t> row;
      while (sstream >> tileCode) // read each word separated by spaces
        row.push_back(tileCode);
      tileData.push_back(row);
    }
    if (tileData.size() > 0)
      init(tileData, levelWidth, levelHeight);
  }
}

// render level
void GameLevel::render(Shader* shader)
{
  for(auto& object : objects)
  {
    if(!object->destroyed)
      object->render(shader);
  }
}

// check if the level is completed (all non-solid tiles are destroyed)
bool GameLevel::isCompleted()
{
  for (const auto& tile : objects)
    if (!tile->isSolid && !tile->destroyed)
      return false;
  return true;
}

// initialize level from tile data
void GameLevel::init(std::vector<std::vector<uint32_t>> tileData, uint32_t levelWidth, uint32_t levelHeight)
{
  // calculate dimensions
  uint32_t height = tileData.size();
  uint32_t width  = tileData[0].size();
  float unit_width = levelWidth / static_cast<float>(width);
  float unit_height = levelHeight / height;
  
  // initialize level tiles based on tileData		
  for (uint32_t y = 0; y < height; ++y)
  {
    for (uint32_t x = 0; x < width; ++x)
    {
      if(tileData[y][x] == 0) continue;

      const glm::vec2 pos(unit_width * x, unit_height * y);
      const glm::vec2 size(unit_width, unit_height);
      Texture2D* texture;
      glm::vec3 color { 1,1,1 };
      bool solid = false;

      if (tileData[y][x] == 1) // solid
      {
        texture = ResourceManager::getTexture("block_solid");
        color = glm::vec3{ 0.8f, 0.8f, 0.7f };
        solid = true;
      }
      else if (tileData[y][x] > 1)
      {
        texture = ResourceManager::getTexture("block");

        if (tileData[y][x] == 2)
          color = glm::vec3{ 0.2f, 0.6f, 1.0f };
        else if (tileData[y][x] == 3)
          color = glm::vec3{ 0.0f, 0.7f, 0.0f };
        else if (tileData[y][x] == 4)
          color = glm::vec3{ 0.8f, 0.8f, 0.4f };
        else if (tileData[y][x] == 5)
          color = glm::vec3{ 1.0f, 0.5f, 0.0f };
      }

      GameObject* obj = new GameObject(GL_STATIC_DRAW, pos, size, texture, color);
      obj->isSolid = solid;

      objects.push_back(obj);
    }
  }
}

void GameLevel::clear()
{
  for(GameObject* o : objects)
    delete o;
  objects.clear();
}