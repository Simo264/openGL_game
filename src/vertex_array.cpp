#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

#include <glm/glm.hpp>
#include <iostream>

VertexArray::VertexArray()
{
  glGenVertexArrays(1, &m_id);
  bind();
}

VertexArray::~VertexArray()
{
  deleteArray();
}

void VertexArray::bind()
{
  glBindVertexArray(m_id);
}

void VertexArray::unbind()
{
  glBindVertexArray(0);
}

void VertexArray::deleteArray()
{
  glDeleteVertexArrays(1, &m_id);
}

void VertexArray::setAttribute(uint32_t index, uint32_t count, uint32_t type, 
    bool normalized, uint64_t stride, const void* pointer)
{
  glVertexAttribPointer(index, count, type, normalized, stride, pointer);
}

void VertexArray::enableAttribute(uint32_t index)
{
  glEnableVertexAttribArray(index);
}

void VertexArray::disableAttribute(uint32_t index)
{
  glDisableVertexAttribArray(index);
}

void VertexArray::addBuffer(VertexBuffer& vb, const VertexBufferLayout& layout)
{
  bind();
  vb.bind();

  const std::vector<BufferElement> elements = layout.getElements();

  for(size_t i = 0; i < elements.size(); i++)
  {
    const auto& e = elements[i];
    setAttribute(i, e.count, e.type, e.normalized, e.stride, e.pointer);
    enableAttribute(i);
  }
}