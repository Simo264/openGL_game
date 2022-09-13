#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>

class Object
{
private:

public:
  Object() = default;
  ~Object() = default;

  virtual void render(const Shader& shader) = 0;
};

#endif