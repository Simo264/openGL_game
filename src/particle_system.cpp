#include "particle_system.h"

#include <GL/glew.h>
#include <glm/gtx/transform.hpp>
#include <random>

ParticleGenerator::ParticleGenerator(Shader* shader, Texture2D* texture, uint32_t amount)
  : Object{GL_STATIC_DRAW},
    m_amount{amount},
    m_shader{shader},
    m_texture{texture},
    m_lastUsedParticle{0}
{
  init();
}

void ParticleGenerator::update(float deltaTime, GameObject* object, uint32_t newParticles, glm::vec2 offset)
{
  // add new particles 
  for (uint32_t i = 0; i < newParticles; ++i)
  {
    int unusedParticle = firstUnusedParticle();
    respawnParticle(&m_particles[unusedParticle], object, offset);
  }
  // update all particles
  for (uint32_t i = 0; i < m_amount; ++i)
  {
    Particle &p = m_particles[i];
    p.life -= deltaTime; // reduce life
    if (p.life > 0.0f)
    {	
      // particle is alive, thus update
      p.position -= p.velocity * deltaTime; 
      p.color.a -= deltaTime * 2.5f;
    }
  }
}

void ParticleGenerator::draw()
{
  m_shader->use();
  m_shader->setMatrix4f("projection", glm::ortho(0.0f, 720.f, 720.f, 0.0f, -1.0f, 1.0f));

  // use additive blending to give it a 'glow' effect
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  for(Particle particle : m_particles)
  {
    if(particle.life > 0.0f)
    {
      m_shader->setVector2f("offset", particle.position);
      m_shader->setVector4f("color", particle.color);
      m_texture->bind();
      m_vertexArray->bind();
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
  }
  // don't forget to reset to default blending mode
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init()
{
  // create amount default particle instances
  for (uint32_t i = 0; i < m_amount; ++i)
    m_particles.push_back(Particle());
}

uint32_t ParticleGenerator::firstUnusedParticle()
{
  // first search from last used particle, this will usually return almost instantly
  for (uint32_t i = m_lastUsedParticle; i < m_amount; ++i){
    if (m_particles[i].life <= 0.0f)
    {
      m_lastUsedParticle = i;
      return i;
    }
  }
  // otherwise, do a linear search
  for (uint32_t i = 0; i < m_lastUsedParticle; ++i){
    if (m_particles[i].life <= 0.0f)
    {
      m_lastUsedParticle = i;
      return i;
    }
  }
  // all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
  m_lastUsedParticle = 0;
  return 0;
}

void ParticleGenerator::respawnParticle(Particle* particle, GameObject* object, glm::vec2 offset)
{
  float random = ((rand() % 100) - 50) / 10.0f;
  float rColor = 0.5f + ((rand() % 100) / 100.0f);
  particle->position = object->position + random + offset;
  particle->color = glm::vec4(rColor, rColor, rColor, 1.0f);
  particle->life = 1.0f;
  particle->velocity = object->velocity * 0.1f;
}