#ifndef GAME_BALL_H
#define GAME_BALL_H

#include "game_object.h"

#include <glm/glm.hpp>

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class GameBall : public GameObject
{
public:
  bool stuck;

  GameBall(
    glm::vec2 position_, 
    glm::vec2 dimension_,
    class Texture2D* texture_,
    glm::vec3 color_,
    float rotation_,
    glm::vec2 velocity_
  );

  // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
  void move(float deltaTime, uint32_t windowWidth);
  
  // resets the ball to original state with given position and velocity
  void reset(glm::vec2 position_, glm::vec2 velocity_);
};

#endif