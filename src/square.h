#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <array>

#include "vertex.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

class Square
{
private:
  VertexArray vertexArray;
  VertexBuffer vertexBuffer;
  IndexBuffer indexBuffer;

public:
  Square(const std::array<Position, 4>& vPositions, 
        const std::array<Color, 4>& vColors,
        const std::array<uint32_t, 6>& vIndices
  )
  {
    const uint32_t sizePos = vPositions.size()*sizeof(Position);
    const uint32_t sizeCol = vColors.size()*sizeof(Color);
    const uint32_t sizeInd = vIndices.size()*sizeof(uint32_t);

    vertexArray.bind();

    vertexBuffer.bind();
    vertexBuffer.bufferData(sizePos + sizeCol, NULL, GL_STATIC_DRAW);
    vertexBuffer.subData(0, sizePos, vPositions.data());
    vertexBuffer.subData(sizePos, sizeCol, vColors.data());
    
    indexBuffer.bind();
    indexBuffer.bufferData(sizeInd, vIndices.data(), GL_STATIC_DRAW);

    vertexArray.setAttribute(0, 2, sizeof(Position), (void*) 0);
    vertexArray.enableAttribute(0);
    vertexArray.setAttribute(1, 3, sizeof(Color), (void*) sizePos);
    vertexArray.enableAttribute(1);
  }

  ~Square()
  {
  }

  void render()
  {
    vertexArray.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
};

#endif