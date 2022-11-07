/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "shader.h"
#include "texture.h"
#include "game_object.h"

#include <vector>
#include <memory>
#include <glm/glm.hpp>

struct Particle {
  glm::vec2 position;
  glm::vec2 velocity;
  glm::vec4 color;
  float life;
  
  Particle() : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
};    

class ParticleGenerator : public Object
{
private:
  // state
  std::vector<Particle> m_particles;
  uint32_t m_amount;
  uint32_t m_lastUsedParticle;
  
  // render state
  Shader* m_shader;
  Texture2D* m_texture;

  uint32_t m_VAO;

  // initializes buffer and vertex attributes
  void init();
  
  // returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
  uint32_t firstUnusedParticle();
  
  // respawns particle
  void respawnParticle(Particle* particle, GameObject* object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));

public:
  ParticleGenerator(Shader* shader, Texture2D* texture, uint32_t amount);

  void update(float deltaTime, GameObject* object, uint32_t newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
  
  // render all particles
  void draw();
};

#endif