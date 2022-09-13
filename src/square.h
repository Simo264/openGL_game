#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <array>

class Square
{
private:
  const std::array<Position, 4> m_localPos = { 
    Position(-0.5f, +0.5f),Position(+0.5f, +0.5f),Position(-0.5f, -0.5f),Position(+0.5f, -0.5f) 
  };
  const std::array<Color, 4> m_colors = {
    Color(1,0,0),Color(0,1,0),Color(0,0,1),Color(0,1,1)
  };
  const std::array<uint32_t, 6> m_indices { 0,1,2, 1,2,3 };

  VertexArray m_vertexArray;
  VertexBuffer m_vertexBuffer;
  IndexBuffer m_indexBuffer;

  glm::mat4 m_scaleMatrix = glm::mat4(1.0f);
  glm::mat4 m_translateMatrix = glm::mat4(1.0f);
  glm::mat4 m_rotateMatrix = glm::mat4(1.0f);

public:
  Square(const glm::mat4& scale = glm::scale(glm::mat4(1.0f), { 1,1,0 }),
    const GLenum usage = GL_DYNAMIC_DRAW);

  ~Square() = default;

  void render(const Shader& shader);

  void setPosition(const std::array<Position, 4>& vPos);
  void setColor(const std::array<Color, 4>& vColors);
  
  void rotate(float angle, glm::vec3 rotationAxis);
  void scale(float x, float y);
  void translate(float x, float y);

  glm::mat4 modelMatrix = glm::mat4(1.0f);
};







Square::Square(const glm::mat4& scale, const GLenum usage)
{
  m_vertexArray.bind();

  m_vertexBuffer.bind();
  m_vertexBuffer.dataBuffer(sizeof(std::array<Position, 4>)+sizeof(std::array<Color, 4>), NULL, usage);
  setPosition(m_localPos);
  setColor(m_colors);
  
  m_indexBuffer.bind();
  m_indexBuffer.bufferData(sizeof(std::array<uint32_t, 6>), m_indices.data(), usage);

  m_vertexArray.setAttribute(0, 2, sizeof(Position), (void*) 0);
  m_vertexArray.enableAttribute(0);
  m_vertexArray.setAttribute(1, 3, sizeof(Color), (void*) sizeof(std::array<Position, 4>));
  m_vertexArray.enableAttribute(1);

  m_scaleMatrix = scale;
  m_translateMatrix = glm::mat4(1.0f);
  m_rotateMatrix = glm::mat4(1.0f);
}

void Square::render(const Shader& shader) 
{
  modelMatrix = m_scaleMatrix * m_translateMatrix * m_rotateMatrix;

  shader.setMatrix4Float("model", modelMatrix);

  m_vertexArray.bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Square::setPosition(const std::array<Position, 4>& vPos)
{ 
  m_vertexBuffer.subDataBuffer(0, sizeof(std::array<Position, 4>), vPos.data());
}

void Square::setColor(const std::array<Color, 4>& vColors)
{
  m_vertexBuffer.subDataBuffer(sizeof(std::array<Position, 4>), sizeof(vColors), vColors.data());
}

void Square::rotate(float angle, glm::vec3 rotationAxis)
{
  m_rotateMatrix = glm::rotate(glm::mat4(1.0f), angle, rotationAxis);
}
void Square::scale(float x, float y)
{
  m_scaleMatrix = glm::scale(glm::mat4(1.0f), { x,y,0 } );
}
void Square::translate(float x, float y)
{
  m_translateMatrix = glm::translate(glm::mat4(1.0f), { x,y,0 });
}

#endif