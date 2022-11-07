#include "collision_detection.h"

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

Collision CollisionDetection::checkCollision(GameBall* ball, GameObject* object)
{
  const auto& ballRadius = ball->radius;

  // get center point circle first 
  glm::vec2 center(ball->position.x + ballRadius, ball->position.y + ballRadius);

  // calculate AABB info (center, half-extents)
  glm::vec2 aabb_half_extents(object->dimension.x / 2.0f, object->dimension.y / 2.0f);
  glm::vec2 aabb_center(
    object->position.x + aabb_half_extents.x, 
    object->position.y + aabb_half_extents.y
  );

  // get difference vector between both centers
  glm::vec2 difference = center - aabb_center;
  glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

  // add clamped value to AABB_center and we get the value of box closest to circle
  glm::vec2 closest = aabb_center + clamped;

  // retrieve vector between center circle and closest point AABB and check if length <= radius
  difference = closest - center;

  if (glm::length(difference) <= ballRadius)
      return std::make_tuple(true, vectorDirection(difference), difference);
  else
    return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

Direction CollisionDetection::vectorDirection(glm::vec2 target)
{
  glm::vec2 compass[] = {
    glm::vec2(0.0f, 1.0f),	// up
    glm::vec2(1.0f, 0.0f),	// right
    glm::vec2(0.0f, -1.0f),	// down
    glm::vec2(-1.0f, 0.0f)	// left
  };
  float max = 0.0f;
  unsigned int best_match = -1;
  for (unsigned int i = 0; i < 4; i++)
  {
    float dot_product = glm::dot(glm::normalize(target), compass[i]);
    if (dot_product > max)
    {
      max = dot_product;
      best_match = i;
    }
  }
  return (Direction)best_match;
}