#include "vertex_array.h"

VertexArray::VertexArray()
{
  glGenVertexArrays(1, &m_id);
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

void VertexArray::addBuffer(VertexBuffer& buffer)
{
  buffer.bind();
}

void VertexArray::addBuffer(IndexBuffer& indexBuffer)
{
  indexBuffer.bind();
}

void VertexArray::setAttribute(uint32_t index, uint32_t size, uint32_t stride, const void* pointer)
{
  glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
}

void VertexArray::enableAttribute(uint32_t index)
{
  glEnableVertexAttribArray(index);
}

void VertexArray::disableAttribute(uint32_t index)
{
  glDisableVertexAttribArray(index);
}

