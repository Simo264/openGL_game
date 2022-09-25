#include "vertex_buffer.h"
#include "vertex.h"

#include <iostream>

VertexBuffer::VertexBuffer()
  : m_bufferSize(0)
{
  glGenBuffers(1, &m_id);
  bind();
}

VertexBuffer::VertexBuffer(uint32_t size, const void* data, GLenum usage)
  : m_bufferSize(0)
{
  glGenBuffers(1, &m_id);
  bind();
  dataBuffer(size, data, usage);
}

VertexBuffer::~VertexBuffer()
{
  deleteBuffer();
}

void VertexBuffer::dataBuffer(uint32_t size, const void* data, GLenum usage)
{
  glBufferData(GL_ARRAY_BUFFER, size, data, usage);
  m_bufferSize = size;
}

void VertexBuffer::subDataBuffer(uint32_t offset, uint32_t size, const void* data)
{
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::deleteBuffer()
{
  glDeleteBuffers(1, &m_id);
}