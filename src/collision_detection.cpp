#include "collision_detection.h"
#include "game_object.h"

bool CollisionDetection::checkCollision(GameObject* one, GameObject* two)
{
  // Box one
  const float& X_MIN_ONE = one->position.x;
  const float& X_MAX_ONE = X_MIN_ONE + one->dimension.x;
  const float& Y_MIN_ONE = one->position.y;
  const float& Y_MAX_ONE = Y_MIN_ONE + one->dimension.y;
  // Box two
  const float& X_MIN_TWO = two->position.x;
  const float& X_MAX_TWO = X_MIN_TWO + two->dimension.x;
  const float& Y_MIN_TWO = two->position.y;
  const float& Y_MAX_TWO = Y_MIN_TWO + two->dimension.y;

  // collision x-axis?
  const bool collisionX = (X_MAX_ONE >= X_MIN_TWO) && (X_MAX_TWO >= X_MIN_ONE);
  // collision y-axis?
  const bool collisionY = (Y_MAX_ONE >= Y_MIN_TWO) && (Y_MAX_TWO >= Y_MIN_ONE);
  // collision only if on both axes
  return collisionX && collisionY;
}