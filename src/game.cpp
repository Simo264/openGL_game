#include "game.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

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
  ResourceManager::loadTexture("../res/block.png", true, "block");
  ResourceManager::loadTexture("../res/block_solid.png", true, "block_solid");
  
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
  const float dTime = static_cast<float>(glfwGetTime());

  Texture2D* texture = ResourceManager::getTexture("face");
  const glm::vec2 position = glm::vec2(0, 0);
  const glm::vec2 size = glm::vec2(1, 1);
  const float rotate = dTime * 100;
  const glm::vec3 color = glm::vec3(sin(dTime), 0.5, 0.5);
  
  m_ptrRenderer->drawSprite(
    texture,
    position,
    size,
    rotate,
    color
  );
}
