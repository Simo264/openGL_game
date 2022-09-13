#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <array>

class Square : public ObjectInterface
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

public:
  Square(GLenum usage = GL_STATIC_DRAW);
  ~Square() = default;

  void render(const Shader& shader) override;
  void setPosition(const std::array<Position, 4>& vPos);
  void setColor(const std::array<Color, 4>& vColors);
};



Square::Square(GLenum usage)
{
  m_vertexArray.bind();

  m_vertexBuffer.bind();
  m_vertexBuffer.dataBuffer(sizeof(std::array<Position, 4>)+sizeof(std::array<Color, 4>), NULL, usage);
  m_vertexBuffer.subDataBuffer(0, sizeof(std::array<Position, 4>), m_localPos.data());
  m_vertexBuffer.subDataBuffer(sizeof(std::array<Position, 4>), sizeof(std::array<Color, 4>), m_colors.data());
  
  m_indexBuffer.bind();
  m_indexBuffer.bufferData(sizeof(std::array<uint32_t, 6>), m_indices.data(), usage);

  m_vertexArray.setAttribute(0, 2, sizeof(Position), (void*) 0);
  m_vertexArray.enableAttribute(0);
  m_vertexArray.setAttribute(1, 3, sizeof(Color), (void*) sizeof(std::array<Position, 4>));
  m_vertexArray.enableAttribute(1);
}

void Square::render(const Shader& shader) 
{
  shader.setMatrix4Float("model", this->getModel());
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

#endif