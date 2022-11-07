#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "game_object.h"
#include "game_ball.h"

#include <tuple>
#include <glm/glm.hpp>

enum Direction { UP, RIGHT, DOWN, LEFT };

using Collision = std::tuple<bool, Direction, glm::vec2>; 

class CollisionDetection
{
public:
  CollisionDetection() { }

  static bool checkCollision(GameObject* one, GameObject* two);

  static Collision checkCollision(GameBall* ball, GameObject* object);

  static Direction vectorDirection(glm::vec2 target);
};

#endif