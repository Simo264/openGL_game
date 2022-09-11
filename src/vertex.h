#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

using Position  = glm::vec2;  // x,y
using Color     = glm::vec3;  // r,g,b

struct Vertex
{
  Position position;
  Color color;
};


#endif