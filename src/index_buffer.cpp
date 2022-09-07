#include "index_buffer.h"

IndexBuffer::IndexBuffer(uint32_t size, const void* data, GLenum usage)
{
  glGenBuffers(1, &m_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage); 
}
IndexBuffer::~IndexBuffer()
{
  glDeleteBuffers(1, &m_buffer);
}
  
void IndexBuffer::bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}
void IndexBuffer::unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}