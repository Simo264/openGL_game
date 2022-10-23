#include "vertex_buffer.h"

#include <GL/glew.h>

VertexBuffer::VertexBuffer()
{
  glGenBuffers(1, &m_id);
  bind();
}

VertexBuffer::VertexBuffer(uint32_t size, const void* data, uint32_t usage)
{
  glGenBuffers(1, &m_id);
  bind();
  bufferData(size, data, usage);
}

VertexBuffer::~VertexBuffer()
{
  deleteBuffer();
}

void VertexBuffer::bufferData(uint32_t size, const void* data, uint32_t usage)
{
  glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::bufferSubData(uint32_t offset, uint32_t size, const void* data)
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