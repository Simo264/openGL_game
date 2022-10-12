/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
  // object state
  glm::vec2 position; 
  glm::vec2 size;
  glm::vec3 color;
  glm::vec2 velocity;

  float rotation;
  bool isSolid;
  bool destroyed;

  // render state
  class Texture2D* sprite = nullptr;	

  GameObject(glm::vec2 position_ = glm::vec2(0.f), 
    glm::vec2 size_ = glm::vec2(1.f), 
    class Texture2D* sprite_ = nullptr, 
    glm::vec3 color = glm::vec3(1.f),
    glm::vec2 velocity_ = glm::vec2(0.f)
  );
  
  // draw sprite
  virtual void draw(class SpriteRenderer* renderer);
};

#endif

