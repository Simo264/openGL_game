#include "game_ball.h"
#include "texture.h"

#include <GL/glew.h>

GameBall::GameBall(glm::vec2 position_, 
  glm::vec2 dimension_,
  Texture2D* texture_,
  glm::vec3 color_,
  float rotation_,
  glm::vec2 velocity_
)
  :GameObject{GL_STATIC_DRAW, position_, dimension_, texture_, color_, rotation_, velocity_},
  stuck { true }
{
}

// moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
void GameBall::move(float deltaTime, uint32_t windowWidth)
{
  if(stuck) return;

  // move the ball
  position += velocity * deltaTime;
  
  // then check if outside window bounds and if so, reverse velocity and restore at correct position
  if (position.x <= 0.0f)
  {
    velocity.x = -velocity.x;
    position.x = 0.0f;
  }
  else if (position.x + dimension.x >= windowWidth)
  {
    velocity.x = -velocity.x;
    position.x = windowWidth - dimension.x;
  }
  if (position.y <= 0.0f)
  {
    velocity.y = -velocity.y;
    position.y = 0.0f;
  }
}
  
// resets the ball to original state with given position and velocity
void GameBall::reset(glm::vec2 position_, glm::vec2 velocity_)
{
  position = position_;
  velocity = velocity_;
  stuck = true;
}