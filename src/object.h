#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>

class Object
{
private:

public:
  Object() = default;
  ~Object() = default;

  virtual void setTranform(const glm::vec4& transform) = 0;
  virtual void render() = 0;
};

#endif