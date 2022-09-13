#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

struct Transformation
{
  glm::mat4 scaling;
  glm::mat4 translation;
  glm::mat4 rotation;

  Transformation()
  {
    scaling = glm::mat4(1.0f);
    translation = glm::mat4(1.0f);
    rotation = glm::mat4(1.0f);
  }
  Transformation(const glm::mat4& s, const glm::mat4& t, const glm::mat4& r)
  {
    scaling = s;
    translation = t;
    rotation = r;
  }
};

#endif