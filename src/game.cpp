#include "game.h"
#include "sprite_renderer.h"
#include "resource_manager.h"


#include <glm/glm.hpp>

Game::Game(uint32_t width, uint32_t height)
{
  
}

Game::~Game()
{

}

void Game::init()
{
  // load shaders
  Shader* shader = ResourceManager::loadShader(
    "../shaders/sprite.vertex.shader", 
    "../shaders/sprite.fragment.shader", 
    nullptr, 
    "sprite"
  );

  // configure shaders
  // glm::mat4 projection = glm::ortho(
  //   0.0f,  // left
  //   static_cast<float>(width),  // right
  //   static_cast<float>(height), // bottom
  //   0.0f,  // top
  //   -1.0f, // near
  //   1.0f   // far
  // );

  shader->setInteger("image", 0);
  // shader->setMatrix4f("projection", projection);

  // load textures
  ResourceManager::loadTexture("../res/awesomeface.png", true, "face");
  
  m_ptrRenderer = std::unique_ptr<SpriteRenderer>(new SpriteRenderer(shader));
}

void Game::processInput(float deltaTime)
{

}

void Game::update(float deltaTime)
{

}

void Game::render()
{
  Texture2D* texture = ResourceManager::getTexture("face");
  glm::vec2 position;
  glm::vec2 size;
  float rotate;
  
  m_ptrRenderer->drawSprite(
    texture,
    position,
    size,
    rotate
  );
}
