#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <array>

#include "vertex_array.h"
#include "vertex_buffer.h"

class Triangle
{
private:
  VertexArray vertexArray;
  VertexBuffer vertexBuffer;

public:
  Triangle(std::array<glm::vec2,3> vPositions, std::array<glm::vec3,3> vColors)
  {
    const uint32_t sizePos = sizeof(vPositions)*sizeof(glm::vec2);
    const uint32_t sizeCol = sizeof(vColors)*sizeof(glm::vec3);

    vertexArray.bind();

    vertexBuffer.bind();
    vertexBuffer.bufferData(sizePos + sizeCol, NULL, GL_STATIC_DRAW);
    vertexBuffer.subData(0, sizePos, vPositions.data());
    vertexBuffer.subData(sizePos, sizeCol, vColors.data());

    vertexArray.setAttribute(0, 2, sizeof(glm::vec2), (void*) 0);
    vertexArray.enableAttribute(0);
    vertexArray.setAttribute(1, 3, sizeof(glm::vec3), (void*) sizePos);
    vertexArray.enableAttribute(1);
  }

  ~Triangle()
  {
  }

  void render()
  {
    vertexArray.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

#endif