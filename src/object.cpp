#include "object.h"

#include <glm/glm.hpp>

Object::Object(uint32_t usage)
{
  glm::vec2 positions[4] = {
    glm::vec2{ 1, 1 }, 
    glm::vec2{ 0, 1 }, 
    glm::vec2{ 1, 0 }, 
    glm::vec2{ 0, 0 }   
  };
  glm::vec2 textCoords[4] = {
    glm::vec2{ 1, 1 }, 
    glm::vec2{ 0, 1 }, 
    glm::vec2{ 1, 0 }, 
    glm::vec2{ 0, 0 }   
  };
  uint32_t indices[6] = { 
    0,1,2,
    1,2,3
  };
  
  m_vertexArray = std::unique_ptr<VertexArray>(new VertexArray());
  
  m_vertexBuffer = std::unique_ptr<VertexBuffer>(
    new VertexBuffer(sizeof(positions)+sizeof(textCoords), nullptr, usage));
  
  m_indexBuffer = std::unique_ptr<IndexBuffer>(
    new IndexBuffer(sizeof(indices), &indices[0], usage));
  
  m_vertexBuffer->bufferSubData(0, sizeof(positions), &positions[0]);
  m_vertexBuffer->bufferSubData(sizeof(positions), sizeof(textCoords), &textCoords[0]);

  VertexBufferLayout layout;
  layout.pushFloats(2, (void*) 0);
  layout.pushFloats(2, (void*) (sizeof(positions)));

  m_vertexArray->addBuffer(*m_vertexBuffer, layout);
}
