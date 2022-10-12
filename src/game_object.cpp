/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game_object.h"
#include "texture2D.h"
#include "sprite_renderer.h"

GameObject::GameObject(glm::vec2 position_, 
  glm::vec2 size_, 
  Texture2D* sprite_, 
  glm::vec3 color_,
  glm::vec2 velocity_)
  
  : position(position_), 
  size(size_), 
  velocity(velocity_), 
  rotation(0.0f), 
  sprite(sprite_), 
  color(color_),
  isSolid(false), 
  destroyed(false) 
{

}


void GameObject::draw(SpriteRenderer* renderer)
{
  renderer->drawSprite(sprite, position, size, rotation);
}