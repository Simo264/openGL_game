#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <array>

class Triangle : public ObjectInterface
{
private:
  VertexArray vertexArray;
  VertexBuffer vertexBuffer;

public:
  Triangle(const std::array<Position, 3>& vPositions, 
    const std::array<Color, 3>& vColors, 
    GLenum usage
  );
  ~Triangle() = default;

  void render(const Shader& shader) override;
};


Triangle::Triangle(const std::array<Position, 3>& vPositions, 
  const std::array<Color, 3>& vColors, GLenum usage)
{
  const uint32_t sizePos = sizeof(vPositions)*sizeof(glm::vec2);
  const uint32_t sizeCol = sizeof(vColors)*sizeof(glm::vec3);

  vertexArray.bind();

  vertexBuffer.bind();
  vertexBuffer.dataBuffer(sizePos + sizeCol, NULL, usage);
  vertexBuffer.subDataBuffer(0, sizePos, vPositions.data());
  vertexBuffer.subDataBuffer(sizePos, sizeCol, vColors.data());

  vertexArray.setAttribute(0, 2, sizeof(glm::vec2), (void*) 0);
  vertexArray.enableAttribute(0);
  vertexArray.setAttribute(1, 3, sizeof(glm::vec3), (void*) sizePos);
  vertexArray.enableAttribute(1);
}

void Triangle::render(const Shader& shader)
{
  shader.setMatrix4Float("model", this->getModel());
  vertexArray.bind();
  glDrawArrays(GL_TRIANGLES, 0, 3);
}


#endif