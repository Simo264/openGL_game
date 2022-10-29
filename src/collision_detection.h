#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include <tuple>
#include <glm/glm.hpp>

enum Direction { UP, RIGHT, DOWN, LEFT };

using Collision = std::tuple<bool, Direction, glm::vec2>; 

class CollisionDetection
{
public:
  CollisionDetection() { }

  static bool checkCollision(class GameObject* one, class GameObject* two);

  static Collision checkCollision(class GameBall* ball, class GameObject* object);

  static Direction vectorDirection(glm::vec2 target);
};

#endif