#include "game.h"
#include "shader.h"
#include "game_object.h"
#include "game_ball.h"

#include "resource_manager.h"
#include "collision_detection.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

GameObject* background; 
GameObject* player; 
GameBall* ball;

// Initial velocity of the Paddle 
static const float PLAYER_SPEED = 5;

// Initial velocity of the Ball
static const glm::vec2 INITIAL_BALL_VELOCITY(
  300 * cos(glm::radians(45)),      
  -(300 * sin(glm::radians(45)))   
);


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
    { 0,0 }
  );

  const glm::vec2 ballDim = { 50,50 };
  ball = new GameBall(
    { player->position.x + (ballDim.x / 2), player->position.y - ballDim.y },
    ballDim,
    ResourceManager::getTexture("ball"),
    { 1,1,1 },
    0.f,
    INITIAL_BALL_VELOCITY
  );
}

void Game::processInput(float deltaTime)
{
  if(state != GAME_ACTIVE) return;

  glm::vec2 playerVelocity = { 0,0 }; 

  // move playerboard
  if(keys[GLFW_KEY_A])
  {
    if(player->position.x >= 0.f)
    {
      playerVelocity.x = PLAYER_SPEED * cos(glm::radians(180.f));
      player->velocity = playerVelocity;
      player->position += playerVelocity;
      
      if (ball->stuck)
        ball->position += playerVelocity;
    }
  }
  else if(keys[GLFW_KEY_D])
  {
    if(player->position.x <= width - player->dimension.x)
    {
      playerVelocity.x = PLAYER_SPEED * cos(glm::radians(0.f));
      player->velocity = playerVelocity;
      player->position += playerVelocity;
      
      if(ball->stuck)
        ball->position += playerVelocity;
    }
  }
  
  if(keys[GLFW_KEY_SPACE])
    ball->stuck = false;
}

void Game::update(float deltaTime)
{
  ball->move(deltaTime, width);

  doCollisions();

  // did ball reach bottom edge?
  if (ball->position.y >= height) 
  {
    resetLevel();
    resetPlayer();
  }
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

    Collision collision = CollisionDetection::checkCollision(ball, object);
    if (std::get<0>(collision)) // if collision is true
    {
      // destroy block if not solid
      if (!object->isSolid)
        object->destroyed = true;

      // collision resolution
      Direction dir = std::get<1>(collision);
      glm::vec2 diff_vector = std::get<2>(collision);
      
      // horizontal collision
      if (dir == LEFT || dir == RIGHT) 
      {
        ball->velocity.x = -ball->velocity.x; // reverse horizontal velocity
        
        // relocate
        float penetration = ball->radius - std::abs(diff_vector.x);
        if (dir == LEFT)
          ball->position.x += penetration; // move ball to right
        
        else
          ball->position.x -= penetration; // move ball to left;
      }
      // vertical collision
      else 
      {
        ball->velocity.y = -ball->velocity.y; // reverse vertical velocity
        // relocate
        float penetration = ball->radius - std::abs(diff_vector.y);
        if (dir == UP)
          ball->position.y -= penetration; // move ball back up
        else
          ball->position.y += penetration; // move ball back down
      }
    }
  }

  Collision result = CollisionDetection::checkCollision(ball, player);
  if (!ball->stuck && std::get<0>(result))
  {
    // check where it hit the board, and change velocity based on where it hit the board
    float centerBoard = player->position.x + player->dimension.x / 2.0f;
    float distance = (ball->position.x + ball->radius) - centerBoard;
    float percentage = distance / (player->dimension.x / 2.0f);
    
    // then move accordingly
    float strength = 2.0f;
    glm::vec2 oldVelocity = ball->velocity;
    ball->velocity.x = 100.f * percentage * strength; 
    ball->velocity.y = -1.0f * abs(ball->velocity.y);
    ball->velocity = glm::normalize(ball->velocity) * glm::length(oldVelocity);
  } 
}


void Game::resetLevel()
{

}

void Game::resetPlayer()
{
  // reset player/ball stats
  player->position = glm::vec2(width / 2.0f - player->dimension.x / 2.0f, height - player->dimension.y);
  ball->reset(player->position + glm::vec2(player->dimension.x / 2.0f - ball->radius, -(ball->radius * 2.0f)), INITIAL_BALL_VELOCITY);
}