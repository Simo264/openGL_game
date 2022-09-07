#include "vertex_buffer.h"
#include "vertex.h"

VertexBuffer::VertexBuffer(uint32_t size, GLenum usage)
{
  glGenBuffers(1, &m_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
  glBufferData(GL_ARRAY_BUFFER, size, NULL, usage);
}

VertexBuffer::VertexBuffer(uint32_t size, const void* data, GLenum usage)
{
  glGenBuffers(1, &m_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
  glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBuffer::~VertexBuffer()
{
  glDeleteBuffers(1, &m_buffer);
}

void VertexBuffer::subData(uint32_t offset, uint32_t size, const void* data)
{
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void VertexBuffer::unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
