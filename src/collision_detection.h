#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

class CollisionDetection
{
public:
  CollisionDetection() { }

  static bool checkCollision(class GameObject* one, class GameObject* two);

};

#endif