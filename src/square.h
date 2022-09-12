#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <array>

class Square : public Object
{
private:
  const std::array<Position, 4> m_localPosition {
    Position(-0.5f, +0.5f),  // top left
    Position(+0.5f, +0.5f),  // top right
    Position(-0.5f, -0.5f),  // bottom left
    Position(+0.5f, -0.5f),  // bottom right
  };
  const std::array<uint32_t, 6> m_vIndices { 0,1,2, 1,2,3 };

  VertexArray m_vertexArray;
  VertexBuffer m_vertexBuffer;
  IndexBuffer m_indexBuffer;

public:
  Square(const std::array<Color, 4>& vColors = { Color(1,0,0), Color(0,1,0), Color(0,0,1), Color(0,1,1) }, 
    const GLenum usage = GL_STATIC_DRAW);

  ~Square() = default;

  Transform transform;

  void render();
  void setTranform(const glm::vec4& transform);

  void setPosition(const std::array<Position, 4>& vPos);
  void setColor(const std::array<Color, 4>& vColors);
  void rotate(float angle, glm::vec3 rotationAxis);
};


Square::Square(const std::array<Color, 4>& vColors, const GLenum usage)
{
  m_vertexArray.bind();

  m_vertexBuffer.bind();
  m_vertexBuffer.dataBuffer(sizeof(m_localPosition)+sizeof(vColors), NULL, usage);
  m_vertexBuffer.subDataBuffer(0, sizeof(m_localPosition), m_localPosition.data());
  setColor(vColors);
  
  m_indexBuffer.bind();
  m_indexBuffer.bufferData(sizeof(m_vIndices), m_vIndices.data(), usage);

  m_vertexArray.setAttribute(0, 2, sizeof(Position), (void*) 0);
  m_vertexArray.enableAttribute(0);
  m_vertexArray.setAttribute(1, 3, sizeof(Color), (void*) sizeof(m_localPosition));
  m_vertexArray.enableAttribute(1);

  transform.view = glm::translate(transform.view, glm::vec3(0.0f, 0.0f, -3.0f));
  transform.projection = glm::perspective(glm::radians(45.0f), (float)720/(float)720, 0.1f, 100.0f);
}

void Square::render() 
{
  m_vertexArray.bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Square::setTranform(const glm::vec4& transform)
{

}

void Square::setColor(const std::array<Color, 4>& vColors)
{
  m_vertexBuffer.subDataBuffer(sizeof(std::array<Position, 4>), sizeof(vColors), vColors.data());
}

void Square::rotate(float angle, glm::vec3 rotationAxis)
{
  transform.model = glm::rotate(transform.model, angle, rotationAxis);
}

#endif