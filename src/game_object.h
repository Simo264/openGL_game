#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "object.h"
#include "texture.h"
#include "shader.h"

#include <cstdint>
#include <glm/glm.hpp>

class GameObject : public Object
{
public:
  glm::vec2 position;
  glm::vec2 dimension;
  Texture2D* texture;
  glm::vec3 color;
  
  float rotation;
  glm::vec2 velocity;

  bool isSolid;
  bool destroyed;

  GameObject(uint32_t usage = 0x88E4,   // GL_STATIC_DRAW
    glm::vec2 position_ = { 0,0 },      
    glm::vec2 dimension_ = { 10,10 }, 
    Texture2D* texture_ = nullptr, 
    glm::vec3 color_ = glm::vec3{ 1,1,1 },
    float rotation_ = { 0.f },
    glm::vec2 velocity_ = { glm::vec2(1.0f) }
  );

  void render(Shader* shader) const;
};

#endif