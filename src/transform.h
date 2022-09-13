#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

struct Transform
{
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 projection;

  Transform()
  {
    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
  }
  Transform(const glm::mat4& m, const glm::mat4& v, const glm::mat4& p)
  {
    model = m;
    view = v;
    projection = p;
  }
};


#endif