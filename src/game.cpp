#include "game.h"
#include "shader.h"
#include "game_object.h"
#include "game_ball.h"

#include "resource_manager.h"
#include "collision_detection.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GameObject* background; 
GameObject* player; 
GameBall* ball;

Game::Game(uint32_t width_, uint32_t height_)
  : state{GAME_ACTIVE}, keys{}, width{width_}, height{height_}
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
  shader->setInteger("image", 0);

  // load textures
  ResourceManager::loadTexture("../res/background.jpg",  false,  "background");
  ResourceManager::loadTexture("../res/paddle.png",      true,   "paddle");
  ResourceManager::loadTexture("../res/ball.png",        true,   "ball");
  ResourceManager::loadTexture("../res/block.png",       false,  "block");
  ResourceManager::loadTexture("../res/block_solid.png", false,  "block_solid");

  // load levels
  levels.push_back(GameLevel("../res/one.lvl",   width, height / 2));
  levels.push_back(GameLevel("../res/two.lvl",   width, height / 2));
  levels.push_back(GameLevel("../res/three.lvl", width, height / 2));
  levels.push_back(GameLevel("../res/four.lvl",  width, height / 2));
  currentLevel = 0;
  
  background = new GameObject(
    GL_STATIC_DRAW,
    { 0,0 },
    { 720,720 },
    ResourceManager::getTexture("background"),
    { 0,1,0 }
  );
  player = new GameObject(
    GL_STATIC_DRAW,
    { 300,700 },
    { 100,20 },
    ResourceManager::getTexture("paddle"),
    { 1,1,1 },
    0.f,
    { 500.f,0 }
  );

  const glm::vec2 ballDim = { 50,50 };
  ball = new GameBall(
    { player->position.x + (ballDim.x / 2), player->position.y - ballDim.y },
    ballDim,
    ResourceManager::getTexture("ball"),
    { 1,1,1 },
    0.f,
    { 100.0f,-350.0f }
  );
}

void Game::processInput(float deltaTime)
{
  if(state != GAME_ACTIVE) return;

  const float velocity = player->velocity.x * deltaTime;
  
  // move playerboard
  if(keys[GLFW_KEY_A])
  {
    if(player->position.x >= 0.f)
    {
      player->position.x -= velocity;
      if (ball->stuck)
        ball->position.x -= velocity;
    }
  }
  else if(keys[GLFW_KEY_D])
  {
    if(player->position.x <= width - player->dimension.x)
    {
      player->position.x += velocity;
      if(ball->stuck)
        ball->position.x += velocity;
    }
  }
  if(keys[GLFW_KEY_SPACE])
    ball->stuck = false;
}

void Game::update(float deltaTime)
{
  ball->move(deltaTime, width);

  doCollisions();
}

void Game::render()
{
  if(state != GAME_ACTIVE) return;

  Shader* shader = ResourceManager::getShader("sprite");

  background->render(shader);

  player->render(shader);
  
  levels[currentLevel].render(shader);

  ball->render(shader);
}

void Game::doCollisions()
{
  for (GameObject* object : levels[currentLevel].objects)
  {
    if(object->destroyed) continue;

    if (CollisionDetection::checkCollision(ball, object))
    {
      if (!object->isSolid)
        object->destroyed = true;
    }
  }
}