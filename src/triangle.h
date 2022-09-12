#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <array>

class Triangle : public Object
{
private:
  VertexArray vertexArray;
  VertexBuffer vertexBuffer;

public:
  Triangle(std::array<glm::vec2,3> vPositions, std::array<glm::vec3,3> vColors);
  ~Triangle() = default;

  void setTransform(const glm::vec4& transform);
  void render();
};


Triangle::Triangle(std::array<glm::vec2,3> vPositions, std::array<glm::vec3,3> vColors)
{
  const uint32_t sizePos = sizeof(vPositions)*sizeof(glm::vec2);
  const uint32_t sizeCol = sizeof(vColors)*sizeof(glm::vec3);

  vertexArray.bind();

  vertexBuffer.bind();
  vertexBuffer.dataBuffer(sizePos + sizeCol, NULL, GL_STATIC_DRAW);
  vertexBuffer.subDataBuffer(0, sizePos, vPositions.data());
  vertexBuffer.subDataBuffer(sizePos, sizeCol, vColors.data());

  vertexArray.setAttribute(0, 2, sizeof(glm::vec2), (void*) 0);
  vertexArray.enableAttribute(0);
  vertexArray.setAttribute(1, 3, sizeof(glm::vec3), (void*) sizePos);
  vertexArray.enableAttribute(1);
}

void Triangle::render()
{
  vertexArray.bind();
  glDrawArrays(GL_TRIANGLES, 0, 3);
}


void Triangle::setTransform(const glm::vec4& transform)
{

}

#endif